# Vectors implementation benchmark

*This is a collection of benchmarks in several languages, aiming to test the implementation of vector libraries.*

The benchmark simply consist of creating vectors for some simple data types, adding lots of values (100000000) one at a time, doing a quick pass on the vectors values in order to compute a checksum, and then remove each value one by one. The goal is to measure how fast the vectors underlying arrays can realloc themselves. Max RAM usage: 1.5 GB.

Full benchmark results (char, int and 16 bytes struct vectors):

- Rust (release + asm):     1.346 s
- Rust (release):           1.601 s
- C:                        2.016 s
- cpp:                      2.960 s
- go:                       3.489 s
- Ada:                      4.076 s
- Nim (GC: arc):            7.077 s
- v (prod):                 7.630 s
- Nim (GC: default):        9.845 s
- v:                        20.20 s
- javascript (node v12):    Crash in 1m 57.226 s with "JavaScript heap out of memory"
- javascript (node v18):    Crash in 53.480 s with "JavaScript heap out of memory"
- javascript (browser):     Crash in 29.926 s with "out of memory"
- Java:                     Crash in 9m 37.881 s with "java.lang.OutOfMemoryError: GC overhead limit exceeded"
- Python:                   Crash in 2m 38.689 s

Partial benchmark results (only char and int vectors):

- javascript (node v12):    6.649 s
- javascript (node v18):    7.484 s
- javascript (browser):     12.861 s
- Java 8 (w/o genericity):  36.450 s
- Java 8 (w/ genericity):   55.256 s
- Python 3:                 1m 14.738 s


Note: be mindful not to include the compile time of the tested targets (e.g for rust use ``` cargo build ``` instead of ``` cargo run ``` and so on).


TODO:

- cleanup the C version code
- C version: does not compile without the -O2 flag !!!
- C version: inline EQ fun?
- uniformisation of types? int -> T, T -> uint64 ?
- more details here on the benchmark goals, and the choice of data structure (random access).
- java lambda functions? https://www.w3schools.com/java/java_lambda.asp
- cleanup ada README, and source files
- ada generics: keep that
- talk about Linux 'time' for measuring...
