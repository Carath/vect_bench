// Note: Java ArrayLists can have at most 2^31 − 1 elements... SHAMEFUL!
import java.util.ArrayList;

public class BenchNoGenerics
{
	public static void main(String[] args)
	{
		// int n = 10;
		int n = 100000000;

		benchChar(n);
		benchInt(n);
		benchPQnode(n);
	}

	public static long benchChar(int n)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<Character> vect = new ArrayList<Character>();

		for (int i = 0; i < n; ++i) {
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
		vect = null;
		System.gc();
		return checksum;
	}

	public static long benchInt(int n)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<Integer> vect = new ArrayList<Integer>();

		for (int i = 0; i < n; ++i) {
			vect.add(i);
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
		vect = null;
		System.gc();
		return checksum;
	}

	public static long benchPQnode(int n)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<PQnode> vect = new ArrayList<PQnode>();

		for (int i = 0; i < n; ++i) {
			PQnode node = new PQnode((double) i, (long) i);
			vect.add(node);
		}

		long checksum = 0;
		for (PQnode x : vect) {
			checksum += (long) x.key + x.item;
		}
		System.out.printf("checksum: %d\n", checksum);

		while (!vect.isEmpty()) {
			vect.remove(vect.size()-1);
		}

		System.out.printf("Length: %d\n\n", vect.size());
		vect = null;
		System.gc();
		return checksum;
	}
}
