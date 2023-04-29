// Note: Java ArrayLists can have at most 2^31-1 elements... SHAMEFUL!
import java.util.ArrayList;

public class BenchNoGenerics
{
	public static void main(String[] args)
	{
		// int n = 10;
		int n = 100_000_000;

		benchChar(n);
		benchInt(n);
		benchPQnode(n);
	}

	public static long benchChar(int n)
	{
		System.out.printf("\nBench with %d samples...\n", n);

		ArrayList<Character> vect = new ArrayList<Character>();

		for (int i = 0; i < n; ++i) {
			vect.add((char) (i % 256));
		}

		System.out.printf("Length: %d\n", vect.size());
		double totalMemory = Runtime.getRuntime().totalMemory() / 1.0e+9;
		System.out.printf("Total memory: %.3f GB\n", totalMemory);

		long checksum = 0;
		for (char x : vect) {
			checksum += (long) x;
		}
		System.out.printf("Checksum: %d\n", checksum);

		while (!vect.isEmpty()) {
			vect.remove(vect.size()-1);
		}

		vect = null;
		System.gc();
		return checksum;
	}

	public static long benchInt(int n)
	{
		System.out.printf("\nBench with %d samples...\n", n);

		ArrayList<Integer> vect = new ArrayList<Integer>();

		for (int i = 0; i < n; ++i) {
			vect.add(i);
		}

		System.out.printf("Length: %d\n", vect.size());
		double totalMemory = Runtime.getRuntime().totalMemory() / 1.0e+9;
		System.out.printf("Total memory: %.3f GB\n", totalMemory);

		long checksum = 0;
		for (int x : vect) {
			checksum += (long) x;
		}
		System.out.printf("Checksum: %d\n", checksum);

		while (!vect.isEmpty()) {
			vect.remove(vect.size()-1);
		}

		vect = null;
		System.gc();
		return checksum;
	}

	public static long benchPQnode(int n)
	{
		System.out.printf("\nBench with %d samples...\n", n);

		ArrayList<PQnode> vect = new ArrayList<PQnode>();

		for (int i = 0; i < n; ++i) {
			PQnode node = new PQnode((double) i, (long) i);
			vect.add(node);
		}

		System.out.printf("Length: %d\n", vect.size());
		double totalMemory = Runtime.getRuntime().totalMemory() / 1.0e+9;
		System.out.printf("Total memory: %.3f GB\n", totalMemory);

		long checksum = 0;
		for (PQnode x : vect) {
			checksum += (long) x.key + x.item;
		}
		System.out.printf("Checksum: %d\n", checksum);

		while (!vect.isEmpty()) {
			vect.remove(vect.size()-1);
		}

		vect = null;
		System.gc();
		return checksum;
	}
}
