public class PQnode
{
	public double key;
	public long item;

	public PQnode(double key, long item) {
		this.key = key;
		this.item = item;
	}

	public static void main(String[] args) {
		PQnode node = new PQnode(1., 2);
		System.out.printf("%f, %d\n", node.key, node.item);
	}
}
