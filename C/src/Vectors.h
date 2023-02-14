// Do not include this directly! Public header has to be vect_instances.h

// - if T is missing, the code below cannot be defined
// - at exit, undefining T for:
//   - easy redefinition of T with another type.
//   - protect against multiple inclusion with the same type.
// Careful tho, yeah.h must be reincluded if type T is redefined to a previous value.

// blabla on T_EQUALITY(a, b) (equality inlining) + undef too

// ... VECT_IMPL to be defined in a single .c file by instantiation!

// VECT_INIT_CAPACITY and VECT_GROWTH_FACTOR can be changed, for each instantiation!

// Careful not to do T* a = v->array or v->array = ...
// Related: issue with: v->array[i] = vect_remove(pq_Node)(v) [FIXED]

// Lib goal: lightweight, safe and fast library of generic vectors.

#ifdef T

#if __cplusplus
extern "C" {
#endif

// #include <stdio.h>
// #include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
// #include <string.h>
// #include <math.h> // for ceil



#define CAT(X,Y) X##_##Y
#define TEMPLATE(X,Y) CAT(Y, X)

// typedef uint16_t idxType;
// typedef uint32_t idxType;
// typedef uint64_t idxType;
typedef size_t idxType;


// 64-bit (unsigned) integers are necessary for proper working of this lib without sacrificing
// some performances when addind elements to a vector, and allow for more than 4.2E9 elements in a vector.
// Indeed with n-bit integers and this lightweight implementation, issues will arise when the elements number
// is greater than (2^n-1) / VECT_GROWTH_FACTOR. With a default factor of 2, this means 32767 with 16-bit,
// 2.1E9 with 32-bit and 9.2E18 with 64-bit integers which is more than enough.

#define Vect(T) TEMPLATE(T, Vect)
typedef struct
{
	// The underlying array of T elements
	T *array;
	idxType size; // actual number of elements (<= capacity)
	idxType capacity; // in elements number. Always > 0. Private
} Vect(T);

// ofuscate the array? Same machine code?

// uint32_t => limit = 2^32 elements or RAM size
// uint32_t vs size_t vs uint64_t ?

// What happens when the max capacity is reached?


#ifndef VECT_INIT_CAPACITY
#define VECT_INIT_CAPACITY 8 // must be > 0
#endif

#ifndef VECT_GROWTH_FACTOR
#define VECT_GROWTH_FACTOR 2.0 // must be > 1
// #define VECT_GROWTH_FACTOR 1.567 // must be > 1
#endif

// ...
// ... rename it as vect_resize() now? NO, possible confusion with 'size' which won't change a bit.

#define vect_setCapacity(T) TEMPLATE(T, vect_setCapacity)
void vect_setCapacity(T)(Vect(T) *vect, idxType newCapacity);

// // Grows or shrinks the vector capacity if possible, depending on 'resizeFactor'.
// #define vect_resize(T) TEMPLATE(T, vect_resize)
// inline void vect_resize(T)(Vect(T) *vect, double resizeFactor)
// {
// 	// assert(resizeFactor > 0.); // preventing an undefined behavior.
// 	// resizeFactor = resizeFactor > 0. ? resizeFactor : 0.; // preventing an undefined behavior.
// 	// resizeFactor = fmax(0., resizeFactor); // preventing an undefined behavior.
// 	// vect_setCapacity(T)(vect, (idxType) ceil(resizeFactor * vect->capacity));

// 	resizeFactor = resizeFactor > 0. ? resizeFactor : 0.; // preventing an undefined behavior.
// 	vect_setCapacity(T)(vect, (idxType) (resizeFactor * vect->capacity));
// 	// vect_setCapacity(T)(vect, (idxType) (resizeFactor * vect->capacity + 0.5)); // without ceil (so no math.h)

// 	// vect_setCapacity(T)(vect, vect->capacity * resizeFactor);
// }



// ...
#define vect_create_c(T) TEMPLATE(T, vect_create_c)
Vect(T)* vect_create_c(T)(idxType capacity);

// ...
#define vect_create(T) TEMPLATE(T, vect_create)
inline Vect(T)* vect_create(T)(void)
{
	return vect_create_c(T)(VECT_INIT_CAPACITY);
}


// // ...
// #define vect_create(T) TEMPLATE(T, vect_create)
// Vect(T)* vect_create(T)(void);







// ...
#define vect_destroy(T) TEMPLATE(T, vect_destroy)
void vect_destroy(T)(Vect(T) **vect);

// Does not shrink the allocated memory.
#define vect_clear(T) TEMPLATE(T, vect_clear)
inline void vect_clear(T)(Vect(T) *vect)
{
	vect->size = 0;
}

// ...
#define vect_isEmpty(T) TEMPLATE(T, vect_isEmpty)
inline bool vect_isEmpty(T)(const Vect(T) *vect)
{
	return vect->size == 0;
}

// ...
#define vect_size(T) TEMPLATE(T, vect_size)
inline idxType vect_size(T)(const Vect(T) *vect)
{
	return vect->size;
}

// ...
#define vect_get(T) TEMPLATE(T, vect_get)
inline T vect_get(T)(const Vect(T) *vect, idxType i)
{
	assert(i < vect->size);
	return vect->array[i];
}

// ...
#define vect_set(T) TEMPLATE(T, vect_set)
inline void vect_set(T)(Vect(T) *vect, idxType i, T value)
{
	assert(i < vect->size);
	vect->array[i] = value;
}

// #include <stdlib.h>

// ...
#define vect_add(T) TEMPLATE(T, vect_add)
inline void vect_add(T)(Vect(T) *vect, T value)
{
	if (vect->size >= vect->capacity) {
		// // vect_setCapacity(T)(vect, (idxType) (vect->capacity * VECT_GROWTH_FACTOR)); // dangerous, assuming no issue...
		// // vect_setCapacity(T)(vect, (idxType) (vect->capacity * VECT_GROWTH_FACTOR + 0.5)); // not the same!!!
		// vect_setCapacity(T)(vect, (idxType) ceil(vect->capacity * VECT_GROWTH_FACTOR)); // ok but uses math.h

		// #define TRUC ((idxType) ((((idxType) 1) << (8*sizeof(idxType)-1)) / (VECT_GROWTH_FACTOR / 2.0)))
		// assert(vect->capacity < TRUC); // makes it slower...
		// // printf("TRUC: %lu\n", TRUC);
		// // exit(0);

		idxType newCapacity = (idxType) (vect->capacity * VECT_GROWTH_FACTOR); // overflows with uint32_t !!!

		// // For uint32_t:
		// #define ZE_MAX 4294967295 // 2^32-1
		// assert(vect->size <= ZE_MAX); // cannot add more!
		// double f = (vect->capacity * VECT_GROWTH_FACTOR);
		// idxType newCapacity = f > ZE_MAX ? ZE_MAX : f;
		// if (vect->capacity < ZE_MAX) {

		// printf("%u\n", newCapacity);

		// vect_setCapacity(T)(vect, newCapacity); // unsafe in some cases!
		// vect_setCapacity(T)(vect, newCapacity > vect->size ? newCapacity : newCapacity+1); // slower with gcc
		// vect_setCapacity(T)(vect, newCapacity == vect->size ? newCapacity+1 : newCapacity);
		vect_setCapacity(T)(vect, newCapacity == vect->size ? vect->size+1 : newCapacity);
		// vect_setCapacity(T)(vect, newCapacity > vect->size ? newCapacity : vect->size+1); // slower with gcc
		// vect_setCapacity(T)(vect, newCapacity == vect->capacity ? vect->capacity+1 : newCapacity); // slower with gcc

		// }

		// TODO:
		// - if capacity > 2^32, lower it down to 2^32.
		// - if size > 2^32, exit with an error message.
	}
	// overflow issue?

	vect->array[vect->size++] = value;
}



// // ...
// // 	// Careful, 2 steps needed: v->array may be reallocated during a vect_remove(pq_Node)() call!
// // 	pq_Node node = vect_remove(pq_Node)(v);
// // 	v->array[0] = node;
// // 	T x = vect_remove(T)(v); VS T x = vect_get(T)(v, v->size-1); vect_remove(T)(v);
// #define vect_remove(T) TEMPLATE(T, vect_remove)
// inline T vect_remove(T)(Vect(T) *vect)
// {
// 	assert(vect->size > 0);

// 	// if (vect->size < vect->capacity / 4)
// 	// 	vect_setCapacity(T)(vect, vect->capacity / 2);

// 	if (vect->size * (VECT_GROWTH_FACTOR * VECT_GROWTH_FACTOR) < vect->capacity)
// 		vect_setCapacity(T)(vect, (idxType) (vect->capacity / VECT_GROWTH_FACTOR));

// 	// if ((idxType) (vect->size * (VECT_GROWTH_FACTOR * VECT_GROWTH_FACTOR)) < vect->capacity)
// 	// 	vect_setCapacity(T)(vect, (idxType) (vect->capacity / VECT_GROWTH_FACTOR));

// 	return vect->array[--vect->size];
// }

// ...
// Use vect_get() to get the last value before deleting it.
#define vect_remove(T) TEMPLATE(T, vect_remove)
inline void vect_remove(T)(Vect(T) *vect)
{
	if (vect->size > 0) {

		// if (vect->size < vect->capacity / 4)
		// 	vect_setCapacity(T)(vect, vect->capacity / 2);

		if (vect->size * (VECT_GROWTH_FACTOR * VECT_GROWTH_FACTOR) < vect->capacity) // left side left as double to prevent overflows.
			vect_setCapacity(T)(vect, (idxType) (vect->capacity / VECT_GROWTH_FACTOR));

		// if ((idxType) (vect->size * (VECT_GROWTH_FACTOR * VECT_GROWTH_FACTOR)) < vect->capacity) // overflow risk!
		// 	vect_setCapacity(T)(vect, (idxType) (vect->capacity / VECT_GROWTH_FACTOR));

		// if (vect->size < (idxType) (vect->capacity / (VECT_GROWTH_FACTOR * VECT_GROWTH_FACTOR))) // right side can be casted to idxType safely...
		// 	vect_setCapacity(T)(vect, (idxType) (vect->capacity / VECT_GROWTH_FACTOR));

		--vect->size;
	}
}



// ...
#define vect_fromArray(T) TEMPLATE(T, vect_fromArray)
Vect(T)* vect_fromArray(T)(const T *array, idxType size);

// ...
#define vect_copy(T) TEMPLATE(T, vect_copy)
Vect(T)* vect_copy(T)(const Vect(T) *vect);

// ...
// ... vect1 = vect2 possible! (same address)
#define vect_merge(T) TEMPLATE(T, vect_merge)
Vect(T)* vect_merge(T)(const Vect(T) *vect1, const Vect(T) *vect2);

// ...
#define vect_filter(T) TEMPLATE(T, vect_filter)
Vect(T)* vect_filter(T)(const Vect(T) *vect, bool (*predicate)(T));

// // ...
// #define vect_print(T) TEMPLATE(T, vect_print)
// void vect_print(T)(const Vect(T) *vect, void (*print)(const T*));


#ifdef T_EQUALITY

// Returns vect->size if 'value' isn't found.
#define vect_index(T) TEMPLATE(T, vect_index)
idxType vect_index(T)(const Vect(T) *vect, T value);

// ...
#define vect_find(T) TEMPLATE(T, vect_find)
inline bool vect_find(T)(const Vect(T) *vect, T value)
{
	return vect_index(T)(vect, value) != vect->size;
}

#endif // T_EQUALITY

#ifdef VECT_IMPL
#include "VectorsImpl.h" // The implementation
#undef VECT_IMPL // .............
#endif // VECT_IMPL

// ...
#ifdef T_EQUALITY
#undef T_EQUALITY // .............
#endif // T_EQUALITY


#if __cplusplus
}
#endif

#undef T // .............
#endif // T
