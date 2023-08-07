// Do not include this file directly. Do not add inclusion protections.

#ifdef VECT_IMPL

#include <stdlib.h>
#include <string.h>

#ifdef likely
#undef likely
#endif

#ifdef unlikely
#undef unlikely
#endif

#ifdef __GNUC__ // clang defines it too!
	#define likely(x)   __builtin_expect(!!(x), 1)
	#define unlikely(x) __builtin_expect(!!(x), 0)
#else
	#define likely(x)   (x)
	#define unlikely(x) (x)
#endif

#ifdef IS_POWER_OF_TWO
#undef IS_POWER_OF_TWO
#endif
#define IS_POWER_OF_TWO(n) ((n) && !((n) & ((n)-1)))

// This private function returns a capacity at least equal to the given capacity and size.
// Additionally, the capacity will be a multiple of VECT_CHUNK. If said capacity is greater
// than the maximum size of a memory block (on 32-bit systems) the program will exit.
#define vect_sanitize_capacity(T) TEMPLATE(T, vect_sanitize_capacity)
static inline idxType vect_sanitize_capacity(T)(idxType capacity, idxType size)
{
	capacity = ((capacity < size ? size : capacity) + VECT_CHUNK-1) & ~(VECT_CHUNK-1);
	assert(((size_t) capacity) == capacity && "Max block size reached on a 32-bit system.");
	return capacity;
}

// Creates a new vector with the given size and at least the given capacity.
// The first 'size' values are guaranteed to be initialized to 0.
Vect(T)* vect_create(T)(idxType capacity, idxType size)
{
	assert(VECT_GROWTH_FACTOR > 1. && VECT_INIT_CAPACITY >= 0 &&
		IS_POWER_OF_TWO(VECT_CHUNK) && "Sanity checks failed.");
	capacity = vect_sanitize_capacity(T)(capacity, size);
	Vect(T) *vect = (Vect(T)*) malloc(sizeof(Vect(T)));
	vect->capacity = capacity;
	vect->size = size;
	vect->array = (T*) calloc(capacity, sizeof(T)); // lazy allocation
	assert(vect->array && "Memory error: cannot allocate the vector.");
	return vect;
}

// Frees the given vector, passed by address.
void vect_destroy(T)(Vect(T) **vect)
{
	if (vect && *vect) {
		free((*vect)->array);
		free(*vect);
		*vect = NULL;
	}
}

// Sets the capacity of the vector to a value at least equal to the desired one and the actual
// vector size. Be mindful not to overuse this function, it may hinder the program performance.
void vect_setCapacity(T)(Vect(T) *vect, idxType newCapacity)
{
	NULL_CHECK(vect);
	newCapacity = vect_sanitize_capacity(T)(newCapacity, vect->size);
	if (likely(newCapacity != vect->capacity)) {
		vect->capacity = newCapacity;
		vect->array = (T*) realloc(vect->array, newCapacity * sizeof(T));
		assert(vect->array && "Memory error: cannot resize the vector.");
	}
}

// Adds the given element at the end of the vector.
void vect_add(T)(Vect(T) *vect, const T value)
{
	NULL_CHECK(vect);
	if (unlikely(vect->size >= vect->capacity))
		vect_setCapacity(T)(vect, (idxType) (vect->capacity * VECT_GROWTH_FACTOR) + 1);
	vect->array[vect->size++] = value;
}

// Removes the last element of the vector. Does nothing on empty vectors.
// Note: use vect_get() to get said value before deleting it.
void vect_remove(T)(Vect(T) *vect)
{
	NULL_CHECK(vect);
	if (likely(vect->size > 0)) {
		--vect->size;
		if (VECT_SHRINK_CAPACITY &&
			unlikely(vect->size * (VECT_GROWTH_FACTOR * VECT_GROWTH_FACTOR) < vect->capacity))
			vect_setCapacity(T)(vect, (idxType) (vect->capacity / VECT_GROWTH_FACTOR));
	}
}

// Creates a vector from a plain array, which is copied.
// Careful, the given array must not be NULL and its size
// needs to be at least equal to the given one.
Vect(T)* vect_fromArray(T)(const T *array, idxType size)
{
	NULL_CHECK(array);
	Vect(T) *vect = vect_create(T)(size, size);
	memcpy(vect->array, array, size * sizeof(T));
	return vect;
}

// Returns a copy of a vector. The vector elements are not
// deep copied. The initial vector capacity is also copied.
Vect(T)* vect_copy(T)(const Vect(T) *vect)
{
	NULL_CHECK(vect);
	Vect(T) *copy = vect_create(T)(vect->capacity, vect->size);
	memcpy(copy->array, vect->array, vect->size * sizeof(T));
	return copy;
}

// Creates a new vector by merging two vectors whose arrays can overlap.
Vect(T)* vect_merge(T)(const Vect(T) *vect1, const Vect(T) *vect2)
{
	NULL_CHECK(vect1 && vect2);
	Vect(T) *merge = vect_create(T)(vect1->capacity + vect2->capacity, vect1->size + vect2->size);
	memcpy(merge->array, vect1->array, vect1->size * sizeof(T));
	memcpy(merge->array + vect1->size, vect2->array, vect2->size * sizeof(T));
	return merge;
}

// Returns a new vector containing only the elements of the input vector
// verifying a given predicate. Elements order and redundancies are preserved.
Vect(T)* vect_filter(T)(const Vect(T) *vect, bool (*predicate)(const T))
{
	NULL_CHECK(vect && predicate);
	Vect(T) *newvect = vect_createEmpty(T)();
	for (idxType i = 0; i < vect->size; ++i) {
		const T value = vect->array[i];
		if (predicate(value))
			vect_add(T)(newvect, value);
	}
	return newvect;
}


#ifdef T_EQUALITY

// Returns the first index at which 'value' appears in the vector.
// If said value is not found, vect->size is returned.
idxType vect_index(T)(const Vect(T) *vect, const T value)
{
	NULL_CHECK(vect);
	for (idxType i = 0; i < vect->size; ++i) {
		if (unlikely(vect_T_equality(T)(vect->array[i], value)))
			return i;
	}
	return vect->size;
}

#endif // T_EQUALITY

#endif // VECT_IMPL
