with Ada.Containers; use Ada.Containers;
with Ada.Containers.Vectors;
with Ada.Text_IO; use Ada.Text_IO;

procedure Benchmark is

	-- package VectInt is new Ada.Containers.Vectors(Index_Type => Natural, Element_Type => Natural);
	package VectInt is new
		Ada.Containers.Vectors
			(Index_Type => Natural,
			Element_Type => Integer);

	use VectInt; -- useful?

	type uint64_t is mod 2 ** 64;

	n : Integer;
	V : VectInt.Vector;
	checksum : uint64_t;

begin

	-- n := 10;
	n := 100000000;

	Put_Line("Bench with" & Integer'Image(n) & " samples...");

	for i in 0..n-1 loop
		V.Append(i);
	end loop;

	checksum := uint64_t(0);
	for E of V loop
		checksum := checksum + uint64_t(E);
	end loop;
	Put_Line("checksum:" & uint64_t'Image(checksum));

	for i in 0..V.Length loop
	-- while not Is_Empty(V) loop
		Delete_Last(V);
	end loop;

	Put_Line("Length:" & Count_Type'Image(V.Length));

end Benchmark;
