// Note: Java ArrayList can have at most 2^31 − 1 elements... SHAMEFUL!
import java.util.ArrayList;

public abstract class Benchmark
{
	public static long bench0(long n)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<Character> vect = new ArrayList<Character>();

		for (long i = 0; i < n; ++i) {
			vect.add((char) (i % 256));
		}

		long checksum = 0;
		for (int x : vect) {
			checksum += (long) x;
		}
		System.out.printf("checksum: %d\n", checksum);

		while (!vect.isEmpty()) {
			vect.remove(vect.size()-1);
		}

		System.out.printf("Length: %d\n\n", vect.size());
		return checksum;
	}

	public static long bench1(long n)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<Integer> vect = new ArrayList<Integer>();

		for (long i = 0; i < n; ++i) {
			vect.add((int) i);
		}

		long checksum = 0;
		for (int x : vect) {
			checksum += (long) x;
		}
		System.out.printf("checksum: %d\n", checksum);

		while (!vect.isEmpty()) {
			vect.remove(vect.size()-1);
		}

		System.out.printf("Length: %d\n\n", vect.size());
		return checksum;
	}

	public static long bench2(long n)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<PQnode> vect = new ArrayList<PQnode>();

		for (long i = 0; i < n; ++i) {
			PQnode node = new PQnode((double) i, i);
			vect.add(node);
		}

		long checksum = 0;
		for (PQnode x : vect) {
			checksum += (long) x.key + (long) x.item;
		}
		System.out.printf("checksum: %d\n", checksum);

		while (!vect.isEmpty()) {
			vect.remove(vect.size()-1);
		}

		System.out.printf("Length: %d\n\n", vect.size());
		return checksum;
	}

	public abstract <T extends Benchmark> T createT(long x);
	public abstract <T extends Benchmark> long hashT();

	public <T extends Benchmark> long bench(long n)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<T> vect = new ArrayList<T>();

		for (long i = 0; i < n; ++i) {
			vect.add(this.createT(i));
		}

		long checksum = 0;
		for (T x : vect) {
			checksum += x.hashT();
		}
		System.out.printf("checksum: %d\n", checksum);

		while (!vect.isEmpty()) {
			vect.remove(vect.size()-1);
		}

		System.out.printf("Length: %d\n\n", vect.size());
		return checksum;
	}

	public static void main(String[] args) {

		// long n = 10;
		long n = 100000000; // OutOfMemoryError: GC overhead limit exceeded

		bench0(n);
		bench1(n);
		// bench2(n);

		// CharBench c = new CharBench(); c.bench(n);
		// IntBench i = new IntBench(); i.bench(n);
		// // PQnodeBench p = new PQnodeBench(); p.bench(n);
	}
}
