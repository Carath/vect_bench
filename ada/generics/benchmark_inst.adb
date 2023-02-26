with Basic_Types;
with Benchmark;

procedure Benchmark_Inst is

	use Basic_Types;

	type U8 is mod 2 ** 8;

	type PQnode is
		record
			key : Long_Float;
			item : U64;
		end record;

	n : Integer;


	package BenchmarkChar is new Benchmark (T => U8);
	use BenchmarkChar;

	function createChar (X : Integer) return U8 is
	begin
		return U8(X mod 256);
	end createChar;

	function hashChar (X : U8) return U64 is
	begin
		return U64(X);
	end hashChar;


	package BenchmarkInt is new Benchmark (T => Integer);
	use BenchmarkInt;

	function createInt (X : Integer) return Integer is
	begin
		return X;
	end createInt;

	function hashInt (X : Integer) return U64 is
	begin
		return U64(X);
	end hashInt;


	package BenchmarkPQnode is new Benchmark (T => PQnode);
	use BenchmarkPQnode;

	function createPQnode (X : Integer) return PQnode is
		node : PQnode;
	begin
		node.key := Long_Float(X);
		node.item := U64(X);
		return node;
	end createPQnode;

	function hashPQnode (X : PQnode) return U64 is
	begin
		return U64(X.key) + X.item;
	end hashPQnode;

begin

	-- n := 10;
	n := 100000000;

	BenchmarkProc(n, createChar'Access, hashChar'Access);
	BenchmarkProc(n, createInt'Access, hashInt'Access);
	BenchmarkProc(n, createPQnode'Access, hashPQnode'Access);

end Benchmark_Inst;
