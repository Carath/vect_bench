struct PQnode {
	key f64
	item u64
}

fn bench[T](n int, create_t fn(int) T, hash_t fn(T) u64) u64 {
	println("\nBench with ${n} samples...")

	mut vec := []T{}

	for i := 0; i < n; i++ {
		vec.insert(vec.len, create_t(i))
	}

	println("Length: ${vec.len}")

	mut checksum := u64(0)
	for _, x in vec {
		checksum += hash_t(x)
	}
	println("Checksum: ${checksum}")

	for vec.len > 0 {
		vec.pop()
	}

	return checksum
}

fn main() {
	// n := 10
	n := 100000000

	bench(n, fn(x int) u8 { return u8(x) }, fn(x u8) u64 { return u64(x) })
	bench(n, fn(x int) int { return x }, fn(x int) u64 { return u64(x) })
	bench(n, fn(x int) PQnode { return PQnode{key: f64(x), item: u64(x)} },
		fn(x PQnode) u64 { return u64(x.key) + u64(x.item)})
}
