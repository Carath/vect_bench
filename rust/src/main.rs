type KeyType = f64;
type ItemType = u64;

// #[repr(C, packed(4))]
struct PQnode {
	key: KeyType,
	item: ItemType
}

fn main() {
	// let n : u64 = 10;
	let n : u64 = 100000000;

	bench(n, |x| x as u8 , |x| *x as u64);
	bench(n, |x| x as u32, |x| *x as u64);
	bench(n, |x| PQnode { key: x as f64, item: x },
			 |x| x.key as u64 + x.item as u64);
}

// #[inline(never)]
fn bench<T>(n: u64, create_t: fn(u64) -> T, hash_t: fn(&T) -> u64) -> u64 {
	println!("Bench with {} samples...", n);

	let mut vec = Vec::new();

	for i in 0..n {
		vec.push(create_t(i));
	}

	let mut checksum : u64 = 0;
	for x in &vec {
		checksum += hash_t(x);
	}
	println!("checksum: {}", checksum);

	while !vec.is_empty() {
		vec.pop();
	}

	println!("Length: {}\n", vec.len());
	return checksum;
}
