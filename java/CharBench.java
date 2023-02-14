public class CharBench extends Benchmark
{
	private char value;

	public CharBench() {}

	public CharBench(char x) {
		this.value = x;
	}

	public CharBench createT(long x) {
		return new CharBench((char) (x % 256));
	}

	public long hashT() {
		return (long) this.value;
	}
}
