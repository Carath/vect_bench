with Basic_Types;

generic
	type T is private;

package Benchmark is

	use Basic_Types;

	type createFunType is access function (X : Integer) return T;

	type hashFunType is access function (X : T) return U64;

	procedure BenchmarkProc (n : Integer; createT : createFunType; hashT : hashFunType);

end Benchmark;
