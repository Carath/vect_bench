#include <stdio.h>
#include <stdlib.h>

// Adding the actual implementation for the 3 vector instanciations in this source file:
#define VECT_IMPL // only define this once per type instanciation!
#include "vect_instances.h"

int main(int argc, char const *argv[])
{
	int n = 10;
	// int n = 100000000;

	// Preventing unwanted compiler optimizations by reading 'n' from file:
	const char path[] = "../samplesNumber.txt";
	FILE *file = fopen(path, "r");
	if (!file) {
		printf("File not found: '%s'\n", path);
		exit(EXIT_FAILURE);
	}
	if (fscanf(file, "%d", &n) != 1) {
		printf("Could not read samples number...\n");
		exit(EXIT_FAILURE);
	}
	fclose(file);

	printf("-> Samples number: %d\n\n", n);

	//////////////////////////////////////////////////
	// 'uint8_t' variant:

	Vect(uint8_t) *v0 = vect_createEmpty(uint8_t)();

	for (int i = 0; i < n; ++i) {
		vect_add(uint8_t)(v0, (uint8_t) i);
	}

	const idxType size0 = vect_size(uint8_t)(v0);
	printf("Size: %lu\n", size0);

	size_t checksum0 = 0;
	for (int i = 0; i < size0; ++i) {
		checksum0 += (size_t) vect_get(uint8_t)(v0, i);
	} printf("checksum0: %lu\n\n", checksum0);

	while (!vect_isEmpty(uint8_t)(v0)) {
		vect_remove(uint8_t)(v0);
	}

	vect_destroy(uint8_t)(&v0);

	//////////////////////////////////////////////////
	// 'uint32_t' variant:

	Vect(uint32_t) *v1 = vect_createEmpty(uint32_t)();

	for (int i = 0; i < n; ++i) {
		vect_add(uint32_t)(v1, (uint32_t) i);
	}

	const idxType size1 = vect_size(uint32_t)(v1);
	printf("Size: %lu\n", size1);

	size_t checksum1 = 0;
	for (int i = 0; i < size1; ++i) {
		checksum1 += (size_t) vect_get(uint32_t)(v1, i);
	} printf("checksum1: %lu\n\n", checksum1);

	while (!vect_isEmpty(uint32_t)(v1)) {
		vect_remove(uint32_t)(v1);
	}

	vect_destroy(uint32_t)(&v1);

	//////////////////////////////////////////////////
	// 'PQnode' variant:

	Vect(PQnode) *v2 = vect_createEmpty(PQnode)();

	for (int i = 0; i < n; ++i) {
		PQnode node = { .key = (double) i, .item = (size_t) i};
		vect_add(PQnode)(v2, node);
	}

	const idxType size2 = vect_size(PQnode)(v2);
	printf("Size: %lu\n", size2);

	size_t checksum2 = 0;
	for (int i = 0; i < size2; ++i) {
		PQnode node = vect_get(PQnode)(v2, i);
		checksum2 += (size_t) node.key + node.item;
	} printf("checksum2: %lu\n\n", checksum2);

	while (!vect_isEmpty(PQnode)(v2)) {
		vect_remove(PQnode)(v2);
	}

	vect_destroy(PQnode)(&v2);

	//////////////////////////////////////////////////

	return 0;
}
