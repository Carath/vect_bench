#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

typedef struct
{
	double key;
	size_t item;
} __attribute__ ((packed, aligned(4))) PQnode;

// template<typename T>
// size_t bench(size_t n, auto createT, auto hashT) // compile with -fconcepts
template<typename T, typename C, typename H>
size_t bench(size_t n, C && createT, H && hashT)
{
	vector<T> vec;

	for (size_t i = 0; i < n; ++i) {
		vec.push_back(createT(i));
	}

	size_t checksum = 0;
	for (size_t i = 0; i < n; ++i) {
		checksum += (size_t) hashT(vec.at(i));
	}
	cout << "checksum: " << checksum << endl;

	while (!vec.empty()) {
		vec.pop_back();
	}

	cout << "Size: " << vec.size() << "\n" << endl;

	// vector<T>().swap(vec); // should be useless.
	return checksum;
}

int main(int argc, char const *argv[])
{
	// size_t n = 10;
	size_t n = 100000000;
	cout << "Samples: " << n << "\n" << endl;

	bench<uint8_t>(n,
		[](size_t x) -> uint8_t { return (uint8_t) x; },
		[](uint8_t x) -> size_t { return (size_t) x; });
	bench<uint32_t>(n,
		[](size_t x) -> uint32_t { return (uint32_t) x; },
		[](uint32_t x) -> size_t { return (size_t) x; });
	bench<PQnode>(n,
		[](size_t x) -> PQnode { return { .key = (double) x, .item = x}; },
		[](PQnode x) -> size_t { return (size_t) x.key + (size_t) x.item; });

	return 0;
}
