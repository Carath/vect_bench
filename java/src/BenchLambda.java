// Note: Java ArrayLists can have at most 2^31 − 1 elements... SHAMEFUL!
import java.util.ArrayList;

interface CreateT<T> {
	public T create(int x);
}

interface HashT<T> {
	public long hash(T x);
}

public class BenchLambda
{
	public static void main(String[] args)
	{
		// int n = 10;
		int n = 100000000;

		bench(n,
			(CreateT<Character>) (x) -> (char) (x % 256),
			(HashT<Character>) (x) -> (long) x
		);

		bench(n,
			(CreateT<Integer>) (x) -> x,
			(HashT<Integer>) (x) -> (long) x
		);

		bench(n,
			(CreateT<PQnode>) (x) -> new PQnode((double) x, (long) x),
			(HashT<PQnode>) (x) -> (long) x.key + x.item
		);
	}

	public static <T> long bench(int n, CreateT<T> c, HashT<T> h)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<T> vect = new ArrayList<T>();

		for (int i = 0; i < n; ++i) {
			vect.add(c.create(i));
		}

		long checksum = 0;
		for (T x : vect) {
			checksum += h.hash(x);
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
