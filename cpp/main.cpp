#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

typedef struct
{
	double key;
	size_t item;
} __attribute__ ((packed, aligned(4))) PQnode;

// template<typename T>
// size_t bench(int n, auto createT, auto hashT) // compile with -fconcepts, only for GCC.
template<typename T, typename C, typename H>
size_t bench(int n, C && createT, H && hashT)
{
	vector<T> vec;

	for (int i = 0; i < n; ++i) {
		vec.push_back(createT(i));
	}

	const int size = vec.size();
	cout << "\nSize: " << size << endl;

	size_t checksum = 0;
	for (int i = 0; i < size; ++i) {
		checksum += (size_t) hashT(vec.at(i));
	}
	cout << "Checksum: " << checksum << endl;

	while (!vec.empty()) {
		vec.pop_back();
	}

	// vector<T>().swap(vec); // should be useless.
	return checksum;
}

int main(int argc, char const *argv[])
{
	int n = 10;
	// int n = 100'000'000;

	// Preventing unwanted compiler optimizations by reading 'n' from file:
	const char path[] = "../samplesNumber.txt";
	std::ifstream file(path);
	if (!file) {
		cout << "File not found: " << path << endl;
		exit(EXIT_FAILURE);
	}
	if (!(file >> n)) {
		cout << "Could not read samples number..." << endl;
		exit(EXIT_FAILURE);
	}

	cout << "Samples number: " << n << endl;

	bench<uint8_t>(n,
		[](int x)     -> uint8_t { return (uint8_t) x; },
		[](uint8_t x) -> size_t  { return (size_t) x; });
	bench<uint32_t>(n,
		[](int x)      -> uint32_t { return (uint32_t) x; },
		[](uint32_t x) -> size_t   { return (size_t) x; });
	bench<PQnode>(n,
		[](int x)    -> PQnode { return { .key = (double) x, .item = (size_t) x}; },
		[](PQnode x) -> size_t { return (size_t) x.key + (size_t) x.item; });

	return 0;
}
