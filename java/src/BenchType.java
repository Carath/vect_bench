// Note: Java ArrayLists can have at most 2^31 − 1 elements... SHAMEFUL!
import java.util.ArrayList;

public abstract class BenchType
{
	public static void main(String[] args)
	{
		// int n = 10;
		int n = 100000000;

		CharType c = new CharType(); c.bench(n);
		IntType i = new IntType(); i.bench(n);
		PQnodeType p = new PQnodeType(); p.bench(n);
	}

	public abstract BenchType create(int x);
	public abstract long hash();

	public long bench(int n)
	{
		System.out.printf("Bench with %d samples...\n", n);

		ArrayList<BenchType> vect = new ArrayList<BenchType>();

		for (int i = 0; i < n; ++i) {
			vect.add(this.create(i));
		}

		long checksum = 0;
		for (BenchType x : vect) {
			checksum += x.hash();
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

class CharType extends BenchType
{
	private char value;

	public CharType() {}

	public CharType(char x) {
		this.value = x;
	}

	public CharType create(int x) {
		return new CharType((char) (x % 256));
	}

	public long hash() {
		return (long) this.value;
	}
}

class IntType extends BenchType
{
	private int value;

	public IntType() {}

	public IntType(int x) {
		this.value = x;
	}

	public IntType create(int x) {
		return new IntType(x);
	}

	public long hash() {
		return (long) this.value;
	}
}

class PQnodeType extends BenchType
{
	private PQnode value;

	public PQnodeType() {}

	public PQnodeType(PQnode x) {
		this.value = x;
	}

	public PQnodeType create(int x) {
		return new PQnodeType(new PQnode((double) x, (long) x));
	}

	public long hash() {
		return (long) this.value.key + this.value.item;
	}
}
