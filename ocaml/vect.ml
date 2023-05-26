(* N.B:
- 'int' type is 64-bit on a 64-bit machine.
- 'float' type is always 64-bit. *)

open Format

module Vect =
	struct
		(* capacity given by the array length. *)
		type 'a vect = {
			mutable arr: 'a array;
			mutable size: int;
			def: 'a; (* default value, necessary evil *)
		}

	let create defVal =
		{ arr = Array.make 0 defVal; def = defVal; size = 0; }

	let append v x =
		let capacity = Array.length v.arr in
		if v.size + 1 > capacity then begin
			let w = Array.make (2*capacity+1) v.def in
			for i=0 to v.size-1 do
				w.(i) <- v.arr.(i)
			done;
			v.arr <- w
		end;
		v.arr.(v.size) <- x;
		v.size <- v.size+1

	(* No shrinking is done. *)
	let remove v =
		if v.size > 0 then
			v.size <- v.size-1
	end;;


let bench n createT hashT =
	let v = Vect.create (createT 0) in
	for i=0 to n-1 do
		Vect.append v (createT i)
	done;
	printf "Size: %d\n" v.size;
	let checksum = ref 0 in
	for i=0 to v.size-1 do
		checksum := !checksum + hashT v.arr.(i)
	done;
	printf "Checksum: %d\n\n" !checksum;
	while v.size > 0 do
		Vect.remove v
	done;
	!checksum
;;

type pqNode = {
	key: float;
	item: int;
};;

(* let n = 10 in *)
let n = 100000000 in
printf "Samples: %d\n\n" n;

let _ = bench n (fun x -> Char.chr (x mod 256)) (fun x -> Char.code x) in
let _ = bench n (fun x -> x) (fun x -> x) in
let _ = bench n (fun x -> { key = float_of_int x; item = x; }) (fun x -> int_of_float x.key + x.item) in
();;
