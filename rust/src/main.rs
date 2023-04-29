use std::mem::size_of_val;

// #[repr(C, packed(4))]
struct PQnode {
	key: f64,
	item: u64
}

fn main() {
	// let n : u32 = 10;
	let n : u32 = 100_000_000;

	bench(n, |x| x as u8 , |x| *x as u64);
	bench(n, |x| x as u32, |x| *x as u64);
	bench(n, |x| PQnode { key: x as f64, item: x as u64 },
			 |x| x.key as u64 + x.item as u64);
}

// #[inline(never)]
fn bench<T>(n: u32, create_t: fn(u32) -> T, hash_t: fn(&T) -> u64) -> u64 {
	println!("\nBench with {} samples...", n);

	let mut vec = Vec::new();

	for i in 0..n {
		vec.push(create_t(i));
	}

	println!("Length: {}", vec.len());
	println!("Element size: {} B", size_of_val(&vec[0]));
	println!("Vector size:  {:.3} GB", size_of_val(&*vec) as f32 / 1.0e+9_f32);

	// let checksum : u64 = vec.iter().map(|x| hash_t(x)).sum();
	let mut checksum : u64 = 0;
	for x in &vec {
		checksum += hash_t(x);
	}
	println!("Checksum: {}", checksum);

	while !vec.is_empty() {
		vec.pop();
	}

	return checksum;
}
