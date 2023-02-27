# Vectors implementation benchmark

*This is a collection of benchmarks in several languages, aiming to test the implementation of vector libraries.*

The benchmark consists in using vectors (i.e dynamic arrays) which are grown by adding a large number of values (here 100000000) one at a time, followed by a quick pass on the vectors values in order to compute a checksum (and make sure the memory has been allocated), and finally remove each value one by one. The goal is to measure how fast the vector underlying array can realloc itself, and comes from the need of quickly growing a data structure while still allowing random access, as is seen with some implementations of priority queues.

Additionally, different types of elements are used to fill the vectors (element size of 8, 32 and 128 bits) in order to both benchmark the implementation speed in different settings and display the use of generics if the language allows to do so. The maximum RAM usage here should be around 1.5 GB.


## Results

Full benchmark results (char, int and 16-byte struct vectors):

| Language                 | Time       | Comment                                                             |
| :----------------------- | :--------: | :------------------------------------------------------------------ |
| Rust (release + asm)     | 1.346 s    | Assembly is only emitted along with the target.                     |
| Rust (release)           | 1.601 s    |                                                                     |
| C                        | 2.016 s    | Homemade vectors and generics.                                      |
| cpp                      | 2.960 s    |                                                                     |
| go                       | 3.489 s    | PGO didn't bring any noticeable improvement.                        |
| Ada                      | 4.076 s    |                                                                     |
| Nim (arc GC)             | 7.077 s    |                                                                     |
| v (prod)                 | 7.630 s    |                                                                     |
| Nim (default GC)         | 9.845 s    |                                                                     |
| v                        | 20.20 s    |                                                                     |
| js (Firefox)             | 29.93 s    | Crash with "out of memory"                                          |
| js (node v18)            | 53.48 s    | Crash with "JavaScript heap out of memory"                          |
| js (node v12)            | 1m 57 s    | Crash with "JavaScript heap out of memory"                          |
| Python 3                 | 2m 39 s    | Crash with "Killed"                                                 |
| Java 8 (w/o generics)    | 9m 38 s    | Crash with "java.lang.OutOfMemoryError: GC overhead limit exceeded" |

Partial benchmark results (only char and int vectors):

| Language                 | Time       | Comment                                                             |
| :----------------------- | :--------: | :------------------------------------------------------------------ |
| js (node v12)            | 6.649 s    |                                                                     |
| js (node v18)            | 7.484 s    |                                                                     |
| js (Firefox)             | 12.86 s    |                                                                     |
| Java 8 (w/o generics)    | 36.45 s    |                                                                     |
| Java 8 (w/ generics)     | 55.26 s    | Using OOP.                                                          |
| Python 3                 | 1m 15 s    |                                                                     |

Notes:
- Most measurements here have been done using the ``` time ``` command available on Linux systems.
- Be mindful not to include the compile time of the tested targets (e.g for rust use ``` cargo build ``` instead of ``` cargo run ``` and so on).


## TODO

- Uniformisation of types? int -> T, T -> uint64 ?
- Cleanup the C version code
- C version: does not compile without the -O2 flag !!!
- C version: inline EQ funcion?
- Java lambda functions? <https://www.w3schools.com/java/java_lambda.asp>
