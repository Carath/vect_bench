import std/strutils, std/strformat, sugar

type
  PQnode* = object
    key: float64
    item: uint64

proc bench[T](n: int, createT: (int) -> T, hashT: (T) -> uint): uint =
  echo &"\nSamples: {n}"

  var vec = newSeq[T](0)

  for i in 0..n-1: # from 0 to n-1 included !!!
    vec.add(createT(i))

  # for i in 0..len(vec)-1:
  #   echo &"{i} -> {vec[i]}"
  #   #echo "$1 -> $2" % [$i, $vec[i]]

  echo &"Length: {len(vec)}"

  var checksum : uint = 0
  for i in 0..len(vec)-1:
    checksum += uint(hashT(vec[i]))
  echo &"Checksum: {checksum}"

  while len(vec) > 0:
    vec.delete(len(vec)-1) # takes O(n) time

  return checksum

#const n = 10
const n = 100000000

var result : uint = 0
result = bench(n, (x : int) => char(x mod 256), (x: char) => uint(x))
result = bench(n, (x : int) => x, (x: int) => uint(x))
result = bench(n, (x : int) => PQnode(key: float64(uint(x)), item: uint64(x)),
  (x: PQnode) => uint(x.key) + uint(x.item))
