#include <stdio.h>

// Those types can be changed as desired:
typedef double KeyType;
typedef size_t ItemType;

typedef struct
{
	KeyType key;
	ItemType item;
} __attribute__ ((packed, aligned(4))) PQnode;


#undef T
#define T uint8_t
#define VECT_IMPL
#include "Vectors.h"

#undef T
#define T uint32_t
#define VECT_IMPL
#include "Vectors.h"

#undef T
#define T PQnode
#define VECT_IMPL
#include "Vectors.h"


int main(void)
{
	// size_t n = 10;
	size_t n = 100000000;

	printf("\n-> Samples number: %lu\n", n);

	//////////////////////////////////////////////////
	// 'uint8_t' variant:

	Vect(uint8_t) *v0 = vect_create(uint8_t)();

	for (idxType i = 0; i < n; ++i) {
		vect_add(uint8_t)(v0, (uint8_t) i);
	}

	size_t checksum0 = 0;
	for (size_t i = 0; i < n; ++i) {
		checksum0 += (size_t) vect_get(uint8_t)(v0, i);
	} printf("checksum0: %lu\n", checksum0);

	while (!vect_isEmpty(uint8_t)(v0)) {
		vect_remove(uint8_t)(v0);
	}

	printf("Size: %lu\n", vect_size(uint8_t)(v0));
	vect_destroy(uint8_t)(&v0);

	//////////////////////////////////////////////////
	// 'uint32_t' variant:

	Vect(uint32_t) *v1 = vect_create(uint32_t)();

	for (idxType i = 0; i < n; ++i) {
		vect_add(uint32_t)(v1, (uint32_t) i);
	}

	size_t checksum1 = 0;
	for (size_t i = 0; i < n; ++i) {
		checksum1 += (size_t) vect_get(uint32_t)(v1, i);
	} printf("checksum1: %lu\n", checksum1);

	while (!vect_isEmpty(uint32_t)(v1)) {
		vect_remove(uint32_t)(v1);
	}

	printf("Size: %lu\n", vect_size(uint32_t)(v1));
	vect_destroy(uint32_t)(&v1);

	//////////////////////////////////////////////////
	// 'PQnode' variant:

	Vect(PQnode) *v2 = vect_create(PQnode)();

	for (idxType i = 0; i < n; ++i) {
		PQnode node = { .key = (double) i, .item = i};
		vect_add(PQnode)(v2, node);
	}

	size_t checksum2 = 0;
	for (size_t i = 0; i < n; ++i) {
		PQnode node = vect_get(PQnode)(v2, i);
		checksum2 += (size_t) node.key + (size_t) node.item;
	} printf("checksum2: %lu\n", checksum2);

	while (!vect_isEmpty(PQnode)(v2)) {
		vect_remove(PQnode)(v2);
	}

	printf("Size: %lu\n", vect_size(PQnode)(v2));
	vect_destroy(PQnode)(&v2);

	//////////////////////////////////////////////////

	return 0;
}
