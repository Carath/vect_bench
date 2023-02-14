public class IntBench extends Benchmark
{
	private int value;

	public IntBench() {}

	public IntBench(int x) {
		this.value = x;
	}

	public IntBench createT(long x) {
		return new IntBench((int) x);
	}

	public long hashT() {
		return (long) this.value;
	}
}
