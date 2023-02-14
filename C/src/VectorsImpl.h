// Do not include this file directly.
// Do not add inclusion protections.

// Remove unneeded libs?

#include <stdio.h>
#include <stdlib.h>
// #include <stdint.h>
// #include <stdbool.h>
// #include <assert.h>
#include <string.h>
// #include <math.h> // for fmax

#define VECT_MAX(x, y) ((x) < (y) ? (y) : (x))


// // stack version, not including the array.
// #define vect_create_c_s(T) TEMPLATE(T, vect_create_c_s)
// Vect(T) vect_create_c_s(T)(idxType capacity)
// {
// 	assert(sizeof(idxType) >= 8 && VECT_GROWTH_FACTOR > 1. && VECT_INIT_CAPACITY > 0 && capacity > 0); // sanity checks.
// 	Vect(T) vect = {
// 		.array = (T*) calloc(capacity, sizeof(T)),
// 		.size = 0,
// 		.capacity = capacity
// 	};
// 	assert(vect.array);
// 	return vect;
// }

// ...
// To be used in vect_create() and vect_fromArray()
Vect(T)* vect_create_c(T)(idxType capacity)
{
	assert(sizeof(idxType) >= 8 && VECT_GROWTH_FACTOR > 1. && VECT_INIT_CAPACITY > 0 && capacity > 0); // sanity checks.
	Vect(T) *vect = (Vect(T)*) calloc(1, sizeof(Vect(T)));
	vect->array = (T*) calloc(capacity, sizeof(T));
	vect->capacity = capacity; // size left to 0
	assert(vect->array);
	// if (!vect->array) {
	// 	puts("Memory error: cannot allocate the vector.");
	// 	exit(EXIT_FAILURE);
	// }
	return vect;
}

// // ...
// Vect(T)* vect_create(T)(void)
// {
// 	return vect_create_c(T)(VECT_INIT_CAPACITY);
// }

// // ...
// Vect(T)* vect_create(T)(void)
// {
// 	assert(sizeof(idxType) >= 8 && VECT_INIT_CAPACITY > 0 && VECT_GROWTH_FACTOR > 1.); // sanity checks.
// 	Vect(T) *vect = (Vect(T)*) calloc(1, sizeof(Vect(T)));
// 	vect->capacity = VECT_INIT_CAPACITY;
// 	vect->array = (T*) calloc(vect->capacity, sizeof(T));
// 	assert(vect && vect->array);
// 	return vect;
// }




// ...
void vect_destroy(T)(Vect(T) **vect)
{
	if (vect && *vect) {
		free((*vect)->array);
		free(*vect);
		*vect = NULL;
	}
}

// ...
void vect_setCapacity(T)(Vect(T) *vect, idxType newCapacity)
{
	newCapacity = VECT_MAX(VECT_MAX(1u, vect->size), newCapacity);
	// printf("Resizing capacity from %u to %u.\n", vect->capacity, newCapacity);
	if (newCapacity != vect->capacity)
		vect->array = (T*) realloc(vect->array, newCapacity * sizeof(T));
	vect->capacity = newCapacity;
	if (!vect->array) {
		puts("Memory error: cannot resize the vector.");
		exit(EXIT_FAILURE);
	}
}

// // ...
// Vect(T)* vect_fromArray(T)(const T *array, idxType size)
// {
// 	Vect(T) *vect = vect_create(T)();
// 	vect->size = size;
// 	if (size > vect->capacity)
// 		vect_setCapacity(T)(vect, size); // 2 alloc...
// 	memcpy(vect->array, array, size * sizeof(T));
// 	return vect;
// }

// ...
Vect(T)* vect_fromArray(T)(const T *array, idxType size)
{
	Vect(T) *vect = vect_create_c(T)(size);
	memcpy(vect->array, array, size * sizeof(T));
	vect->size = size;
	return vect;
}

// ...
Vect(T)* vect_copy(T)(const Vect(T) *vect)
{
	// Vect(T) *copy = vect_create_c(T)(vect->capacity);
	// memcpy(copy->array, vect->array, vect->size * sizeof(T));
	// copy->size = vect->size;
	// return copy;

	Vect(T) *copy = (Vect(T)*) calloc(1, sizeof(Vect(T)));
	copy->size = vect->size;
	copy->capacity = vect->capacity;
	copy->array = (T*) malloc(copy->capacity * sizeof(T));
	if (!copy->array) {
		puts("Memory error: cannot copy the vector.");
		exit(EXIT_FAILURE);
	}
	memcpy(copy->array, vect->array, vect->size * sizeof(T));
	return copy;
}

// ...
// ... vect1 = vect2 possible! (same address)
Vect(T)* vect_merge(T)(const Vect(T) *vect1, const Vect(T) *vect2)
{
	// Vect(T) *merged = vect_create_c(T)(vect1->capacity + vect2->capacity);
	// memcpy(merged->array, vect1->array, vect1->size * sizeof(T));
	// memcpy(merged->array + vect1->size, vect2->array, vect2->size * sizeof(T));
	// merged->size = vect1->size + vect2->size;
	// return merged;

	Vect(T) *merged = (Vect(T)*) calloc(1, sizeof(Vect(T)));
	merged->size = vect1->size + vect2->size;
	merged->capacity = vect1->capacity + vect2->capacity;
	merged->array = (T*) malloc(merged->capacity * sizeof(T));
	if (!merged->array) {
		puts("Memory error: cannot merge the vectors.");
		exit(EXIT_FAILURE);
	}
	memcpy(merged->array, vect1->array, vect1->size * sizeof(T));
	memcpy(merged->array + vect1->size, vect2->array, vect2->size * sizeof(T));
	return merged;
}

// ...
Vect(T)* vect_filter(T)(const Vect(T) *vect, bool (*predicate)(T))
{
	Vect(T) *newvect = vect_create(T)();
	for (idxType i = 0; i < vect->size; ++i) {
		if (predicate(vect->array[i]))
			vect_add(T)(newvect, vect->array[i]);
	}
	return newvect;
}

// // ...
// void vect_print(T)(const Vect(T) *vect, void (*print)(const T*))
// {
// 	for (idxType i = 0; i < vect->size-1; ++i) {
// 		print(vect->array + i);
// 		puts(", ");
// 	}
// 	print(vect->array + vect->size-1);
// 	puts("\n");
// }


#ifdef T_EQUALITY

// Returns vect->size if 'value' isn't found.
idxType vect_index(T)(const Vect(T) *vect, T value)
{
	for (idxType i = 0; i < vect->size; ++i) {
		T x = vect->array[i];
		if (T_EQUALITY(x, value))
			return i;
	}
	return vect->size;
}


#endif // T_EQUALITY

#undef VECT_MAX
