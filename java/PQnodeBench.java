public class PQnodeBench extends Benchmark
{
	private PQnode value;

	public PQnodeBench() {}

	public PQnodeBench(PQnode x) {
		this.value = x;
	}

	public PQnodeBench createT(long x) {
		return new PQnodeBench(new PQnode((double) x, x));
	}

	public long hashT() {
		return (long) this.value.key + (long) this.value.item;
	}
}
