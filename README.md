# Vectors implementation benchmark

*This is a collection of benchmarks in several languages, aiming to test the implementation of vector libraries.*

The benchmark consists in using vectors (i.e a reallocating array) which are grown by adding a large number of values (here 100000000) one at a time, followed by a quick pass on the vectors values in order to compute a checksum (and make sure the memory has been allocated), and finally remove each value one by one. The goal is to measure how fast the vector underlying array can realloc itself, and comes from the need of quickly growing a data structure while still allowing O(1) random access, as is seen with some implementations of priority queues. Additionally, different types of elements are used to fill the vectors (elements size of 8, 32 and 128 bits) in order to both benchmark the implementation speed in different settings and display the use of generics if the language allows to do so. The maximum RAM usage here should be around 1.5 GB.


## Results

Full benchmark results (char, int and 16-byte struct vectors):

- Rust (release + asm):     1.346 s
- Rust (release):           1.601 s
- C:                        2.016 s
- cpp:                      2.960 s
- go:                       3.489 s
- Ada:                      4.076 s
- Nim (arc GC):             7.077 s
- v (prod):                 7.630 s
- Nim (default GC):         9.845 s
- v:                        20.20 s
- js (node v12):            Crash in 1m 57.226 s with "JavaScript heap out of memory"
- js (node v18):            Crash in 53.480 s with "JavaScript heap out of memory"
- js (Firefox):             Crash in 29.926 s with "out of memory"
- Java:                     Crash in 9m 37.881 s with "java.lang.OutOfMemoryError: GC overhead limit exceeded"
- Python:                   Crash in 2m 38.689 s

Partial benchmark results (only char and int vectors):

- js (node v12):            6.649 s
- js (node v18):            7.484 s
- js (Firefox):             12.861 s
- Java 8 (w/o genericity):  36.450 s
- Java 8 (w/ genericity):   55.256 s
- Python 3:                 1m 14.738 s

Notes:
- Most measurements here have been done using the ``` time ``` command available on Linux systems.
- Be mindful not to include the compile time of the tested targets (e.g for rust use ``` cargo build ``` instead of ``` cargo run ``` and so on).


## TODO

- Uniformisation of types? int -> T, T -> uint64 ?
- Cleanup the C version code
- C version: does not compile without the -O2 flag !!!
- C version: inline EQ fun?
- Java lambda functions? https://www.w3schools.com/java/java_lambda.asp
