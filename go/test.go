package main

import "fmt"

type PQnode struct {
	key float64
	item uint64
}

func bench[T any](n int, create_t func(int) T, hash_t func(T) uint64) uint64 {
	fmt.Printf("Bench with %d samples...\n", n)

	vec := []T{}

	for i := 0; i < n; i++ {
		vec = append(vec, create_t(i))
	}

	checksum := uint64(0)
	for _, x := range vec {
		checksum += hash_t(x)
	}
	fmt.Printf("checksum: %d\n", checksum)

	for len(vec) > 0 {
		vec = vec[:len(vec)-1]
	}

	fmt.Printf("Length: %d\n\n", len(vec))
	return checksum
}

func main() {
	// n := 10
	n := 100000000

	bench(n, func(x int) byte { return byte(x) }, func(x byte) uint64 { return uint64(x) })
	bench(n, func(x int) int { return x }, func(x int) uint64 { return uint64(x) })
	bench(n, func(x int) PQnode { return PQnode{key: float64(x), item: uint64(x)} },
		func(x PQnode) uint64 { return uint64(x.key) + uint64(x.item)})
}
