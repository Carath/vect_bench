package main

import "fmt"
import "runtime"

type PQnode struct {
	key float64
	item uint64
}

func main() {
	thebenchmark();
}

func thebenchmark() {
	// n := 10
	n := 100_000_000

	bench(n, func(x int) byte { return byte(x) }, func(x byte) uint64 { return uint64(x) })
	bench(n, func(x int) int { return x }, func(x int) uint64 { return uint64(x) })
	bench(n, func(x int) PQnode { return PQnode{key: float64(x), item: uint64(x)} },
		func(x PQnode) uint64 { return uint64(x.key) + uint64(x.item)})
}

func bench[T any](n int, create_t func(int) T, hash_t func(T) uint64) uint64 {
	fmt.Printf("\nBench with %d samples...\n", n)

	vec := []T{}

	for i := 0; i < n; i++ {
		vec = append(vec, create_t(i))
	}

	fmt.Printf("Length: %d\n", len(vec))
	var m runtime.MemStats
	runtime.ReadMemStats(&m)
	fmt.Printf("Memory: %.3f GB\n", float32(m.Alloc) / 1.0e+9)

	checksum := uint64(0)
	for _, x := range vec {
		checksum += hash_t(x)
	}
	fmt.Printf("Checksum: %d\n", checksum)

	for len(vec) > 0 {
		vec = vec[:len(vec)-1]
	}

	return checksum
}
