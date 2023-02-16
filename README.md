# Vectors implementation benchmark

*This is a collection of benchmarks in several languages, aiming to test the implementation of vector libraries.*

The benchmark simply consist of creating vectors for some simple data types, adding lots of values (100000000) one at a time, doing a quick pass on the vectors values in order to compute a checksum, and then remove each value one by one. The goal is to measure how fast the vectors underlying arrays can realloc themselves. Max RAM usage: 1.5 GB.

Full benchmark results (char, int and 16 bytes struct vectors):

- Rust (releast + asm):  1.346 s
- Rust (release):        1.601 s
- C:                     2.016 s
- cpp:                   2.960 s
- go:                    3.549 s
- Nim (GC: arc):         7.077 s
- v (prod):              7.630 s
- Nim (GC: default):     9.845 s
- v:                     20.20 s
- Java:                  Crash with "java.lang.OutOfMemoryError: GC overhead limit exceeded" after 9m37,881s
- Python:                Crash after 2m38,689s

Partial benchmark results (only char and int vectors):

- Java:                  36.450 s w/o genericity, 55.256 s with.
- Python:                1m14,738s


Note: be mindful not to include the compile time of the tested targets (e.g for rust use ``` cargo build ``` instead of ``` cargo run ``` and so on).


TODO:

- C version: does not compile without the -O2 flag !!!
- uniformisation of types? int -> T, T -> uint64 ?
