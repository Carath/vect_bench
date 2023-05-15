////////////////////////////////////////////////////////////////////////////////
// About
// -----
// This small library is a C implementation of generic vectors (i.e dynamic arrays)
// for 32-bit and 64-bit systems. It is designed to be fast, lightweight, and safe:
// bound checking is done (unless asserts are disabled). Furthermore memory footprint
// will scale dynamically according to a vector's current number of elements.
//
// Usage
// -----
// To use this in another project, simply copy the 'Vectors.h' and 'VectorsImpl.h' files.
// The first header can be included anywhere to expose the library API, once per type
// instantiation. The second header shouldn't be included directly. In order to instantiate
// the API for vectors with elements of the desired type, said type must be specified before
// including the 'Vectors.h' file. Below is an example for the 'int' type:
//
//   #define T int
//   #include "Vectors.h"
//
// Note that what precedes does not instantiate the actual implementation, doing so requires
// to define the VECT_IMPL symbol before the header inclusion in a chosen source file.
// Be wary that this must be done only *once* per vector type instantiation globally.
// Finally, if the target type contains a * or a keyword like const, unsigned, struct, union,
// enum... then it has to be wrapped in a typedef for this to work.
//
// Parameters
// ----------
// Some macro parameters (see below for their purpose) can be changed from their default values
// from outside the library, and so for each type instantiation. To do so simply redefine them
// with a chosen value before including the Vectors.h header. Additionally, further functions can
// be made available for a given type if the macro T_EQUALITY is defined (again before this header
// inclusion). This macro must encode the equality relationship between 2 elements of that type.
//
// Guarantees
// ----------
// - This library will work on 32-bit systems until the maximum block size is reached
//   (2^32 values). There shouldn't be such issues on 64-bit machines on which the RAM
//   quantity will be the limiting factor.
// - At any given time, a vector size and capacity shall verify: 0 <= size <= capacity
// - Upon creation of a vector of a given size, the array values at index within
//   0 and size-1 included will be initialized to 0.
// - A vector's capacity will be a multiple of the VECT_CHUNK parameter.
// - Basic vector accessors like vect_size(T) will be inlined, thus have zero overhead.
//
// Limitations
// -----------
// - This *must* be compiled with some optimization flag. Typically -O2, or at least -O.
// - It is ill advised to copy a vector's array address or modify it, for it may break
//   the library or user code, since the array will be reallocated internally. Similarly,
//   changing a vector's size or capacity should be done with caution.
// - There may be a speed penalty when the implementation instantiation is located in
//   another source file than where it is used. Using LTO (see makefile) may mitigate this.
//
////////////////////////////////////////////////////////////////////////////////

// Parameters - those can be changed from outside for each instantiation.

// VECT_SHRINK_CAPACITY: when set to 1, the allocated memory can shrink upon element removal.
// Disabling this with a value of 0 may yield speed gains, despite an increased memory usage.
// In that case, one can manually shrink the excess memory of a vector v without removing
// its elements by calling: vect_setCapacity(T)(v, 0);
#ifndef VECT_SHRINK_CAPACITY
#define VECT_SHRINK_CAPACITY 1
#endif

// VECT_GROWTH_FACTOR: used for resizing the array. It must be > 1,
// and can either be an integer (typically 2) or a floating point value.
#ifndef VECT_GROWTH_FACTOR
#define VECT_GROWTH_FACTOR 2
#endif

// VECT_INIT_CAPACITY: minimum capacity of an empty vector upon creation. Must be >= 0.
#ifndef VECT_INIT_CAPACITY
#define VECT_INIT_CAPACITY 0
#endif

// VECT_CHUNK: a power of two of which any vector's capacity will be a multiple.
#ifndef VECT_CHUNK
#define VECT_CHUNK 8
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef VECT_VERSION
#undef VECT_VERSION
#endif
#define VECT_VERSION 1.2

#ifdef T

#if __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#ifdef CAT
#undef CAT
#endif
#define CAT(X,Y) X##_##Y

#ifdef TEMPLATE
#undef TEMPLATE
#endif
#define TEMPLATE(X,Y) CAT(Y, X)

#ifdef idxType
#undef idxType
#endif
#define idxType uint64_t // needed to prevent overflows

////////////////////////////////////////////////////////////////////////////////

#define Vect(T) TEMPLATE(T, Vect)
typedef struct
{
	T *array; // the underlying array of T-type elements
	idxType size; // actual number of elements (<= capacity)
	idxType capacity; // current maximum number of elements
} Vect(T);


// Creates a new vector with the given size and at least the given capacity.
// The first 'size' values are guaranteed to be initialized to 0.
#define vect_create(T) TEMPLATE(T, vect_create)
Vect(T)* vect_create(T)(idxType capacity, idxType size);

// Creates a new empty vector, of capacity at least equal to VECT_INIT_CAPACITY.
#define vect_createEmpty(T) TEMPLATE(T, vect_createEmpty)
inline Vect(T)* vect_createEmpty(T)(void)
{
	return vect_create(T)(VECT_INIT_CAPACITY, 0);
}

// Frees the given vector, passed by address.
#define vect_destroy(T) TEMPLATE(T, vect_destroy)
void vect_destroy(T)(Vect(T) **vect);

// Sets the capacity of the vector to a value at least equal to the desired one and the actual
// vector size. Be mindful not to overuse this function, it may hinder the program performance.
#define vect_setCapacity(T) TEMPLATE(T, vect_setCapacity)
void vect_setCapacity(T)(Vect(T) *vect, idxType newCapacity);

// Sets the vector size to 0. This does not shrink
// the allocated memory or change its values.
#define vect_clear(T) TEMPLATE(T, vect_clear)
inline void vect_clear(T)(Vect(T) *vect)
{
	vect->size = 0;
}

// Checks if the vector is empty.
#define vect_isEmpty(T) TEMPLATE(T, vect_isEmpty)
inline bool vect_isEmpty(T)(const Vect(T) *vect)
{
	return vect->size == 0;
}

// Returns the vector size.
#define vect_size(T) TEMPLATE(T, vect_size)
inline idxType vect_size(T)(const Vect(T) *vect)
{
	return vect->size;
}

// Returns the vector capacity.
#define vect_capacity(T) TEMPLATE(T, vect_capacity)
inline idxType vect_capacity(T)(const Vect(T) *vect)
{
	return vect->capacity;
}

// Returns the element at index i. Does bound checking.
#define vect_get(T) TEMPLATE(T, vect_get)
inline T vect_get(T)(const Vect(T) *vect, idxType i)
{
	assert(i < vect->size && "Out of bound error in vect_get()");
	return vect->array[i];
}

// Sets the element at index i with the given value. Does bound checking.
#define vect_set(T) TEMPLATE(T, vect_set)
inline void vect_set(T)(Vect(T) *vect, idxType i, const T value)
{
	assert(i < vect->size && "Out of bound error in vect_set()");
	vect->array[i] = value;
}

// Adds the given element at the end of the vector.
#define vect_add(T) TEMPLATE(T, vect_add)
void vect_add(T)(Vect(T) *vect, const T value);

// Removes the last element of the vector. Does nothing on empty vectors.
// Note: use vect_get() to get said value before deleting it.
#define vect_remove(T) TEMPLATE(T, vect_remove)
void vect_remove(T)(Vect(T) *vect);

// Creates a vector from a plain array, which is copied.
// Careful, the given array size must be correct.
#define vect_fromArray(T) TEMPLATE(T, vect_fromArray)
Vect(T)* vect_fromArray(T)(const T *array, idxType size);

// Returns a copy of a vector. The vector elements are not
// deep copied. The initial vector capacity is also copied.
#define vect_copy(T) TEMPLATE(T, vect_copy)
Vect(T)* vect_copy(T)(const Vect(T) *vect);

// Creates a new vector by merging two vectors whose arrays can overlap.
#define vect_merge(T) TEMPLATE(T, vect_merge)
Vect(T)* vect_merge(T)(const Vect(T) *vect1, const Vect(T) *vect2);

// Returns a new vector containing only the elements of the input vector
// verifying a given predicate. Elements order and redundancies are preserved.
#define vect_filter(T) TEMPLATE(T, vect_filter)
Vect(T)* vect_filter(T)(const Vect(T) *vect, bool (*predicate)(const T));


#ifdef T_EQUALITY

// Function for testing T-type equality. This is cleaner
// than using the given macro which will be undef anyway.
#define vect_T_equality(T) TEMPLATE(T, vect_T_equality)
inline bool vect_T_equality(T)(const T x, const T y)
{
	return T_EQUALITY(x, y);
}

// Returns the first index at which 'value' appears in the vector.
// If said value is not found, vect->size is returned.
#define vect_index(T) TEMPLATE(T, vect_index)
idxType vect_index(T)(const Vect(T) *vect, const T value);

// Checks if the given value is present in the vector.
#define vect_isIn(T) TEMPLATE(T, vect_isIn)
inline bool vect_isIn(T)(const Vect(T) *vect, const T value)
{
	return vect_index(T)(vect, value) != vect->size;
}

#endif // T_EQUALITY

////////////////////////////////////////////////////////////////////////////////

#include "VectorsImpl.h" // the implementation.

#ifdef T_EQUALITY
#undef T_EQUALITY // to prevent leaking T_EQUALITY to another instantiation.
#endif // T_EQUALITY

#if __cplusplus
}
#endif

#undef T // to prevent leaking T to another instantiation.
#endif // T
