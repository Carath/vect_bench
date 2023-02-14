Benchmark results:

(careful when compiling rust with cargo, do not include compile time!)

Compilation time (from scratch):

- g++:    0.259 s
- gcc:    0.138 s
- cargo:  0.430 s w/o optimizations, 0.420 s w/ optimizations
- javac:  0.389 s


New bench: char + int + PQnode (1.5 GB max RAM usage)

- Rust (releast + asm):  1.364 s
- Rust (release):        1.601 s
- C:                     2.016 s
- cpp:                   2.960 s
- Go:                    3.549 s
- Nim (GC: arc):         7.077 s
- Nim (GC: default):     9.845 s
- v:                     20.20 s
- Java:                  Crash with "java.lang.OutOfMemoryError: GC overhead limit exceeded" after 9m37,881s
                         First 2 benchs in 36.450 s w/o genericity (55.256 s with).
- Python:                Crash after 2m38,689s
                         First 2 benchs: 1m14,738s


TODO:

- C version: does not compile without the -O2 flag !!!
- Go: produce a working example.
- Rust: asm thingy. Cleanup the README.
- global .git/ ?
- uniformisation of types? int -> T, T -> uint64 ?

