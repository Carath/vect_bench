with Ada.Containers; use Ada.Containers;
with Ada.Containers.Vectors;
with Ada.Text_IO; use Ada.Text_IO;

package body Benchmark is

procedure BenchmarkProc (n : Integer; createT : createFunType; hashT : hashFunType) is

	package VectT is new Ada.Containers.Vectors(
		Index_Type => Natural, Element_Type => T);

	use VectT;
	V : VectT.Vector;

	checksum : U64;

begin

	Put_Line("Bench with" & Integer'Image(n) & " samples...");
	Put_Line("Element size:" & Integer'Image(T'Size / 8));

	for i in 0..n-1 loop -- last bound included!
		V.Append(createT(i));
	end loop;

	Put_Line("Length:" & Count_Type'Image(V.Length));

	checksum := U64(0);
	for E of V loop
		checksum := checksum + hashT(E);
	end loop;
	Put_Line("Checksum:" & U64'Image(checksum));

	for i in 0..V.Length-1 loop
	-- while not Is_Empty(V) loop
		V.Delete_Last;
	end loop;

	New_Line;

end BenchmarkProc;

end Benchmark;
