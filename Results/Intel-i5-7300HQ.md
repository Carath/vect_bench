# Intel i5-7300HQ results

Tests done on an Intel i5-7300HQ @ 2.50 GHz, on Ubuntu 20.04.

Note: only average times are reported here, since they do match with median times.


#### Full benchmark results (char, int and 16-byte struct vectors):

| Language                 | Time       | Max RAM   | Comment                                                 |
| :----------------------- | :--------: | :-------: | :------------------------------------------------------ |
| Rust (release + asm)     | 1.352 s    | 1.6 GB    | Assembly is only emitted along with the target.         |
| C (clang 10.0.0)         | 1.386 s    | 1.6 GB    | Homemade vectors and generics (v1.2).                   |
| Rust (release)           | 1.548 s    | 1.6 GB    |                                                         |
| C (gcc 9.4.0)            | 2.170 s    | 1.6 GB    | Homemade vectors and generics (v1.2).                   |
| C++ (clang++ 10.0.0)     | 2.675 s    | 2.1 GB    |                                                         |
| C++ (g++ 9.4.0)          | 2.995 s    | 2.1 GB    |                                                         |
| Swift (release)          | 3.036 s    | 2.1 GB    |                                                         |
| go                       | 3.489 s    | 7.6 GB    | PGO didn't bring any noticeable improvement.            |
| Ada                      | 4.076 s    | 2.1 GB    |                                                         |
| Nim (arc GC)             | 7.077 s    | 6.4 GB    |                                                         |
| v (prod)                 | 7.630 s    | 4.9 GB    | Compiling is very slow in production mode.              |
| Nim (default GC)         | 9.845 s    | 7.6 GB    |                                                         |
| Java 17 (w/o generics)   | 13.26 s    | 5.5 GB    | OpenJDK implementation                                  |
| Java 17 (w/ lambdas)     | 13.71 s    | 5.5 GB    | OpenJDK implementation                                  |
| Java 17 (w/ OOP)         | 15.60 s    | 7.5 GB    | OpenJDK implementation                                  |
| v                        | 20.20 s    | 5.4 GB    |                                                         |
| OCaml (native)           | 23.78 s    | 5.9 GB    |                                                         |
| OCaml (bytecode)         | 52.71 s    | 5.9 GB    |                                                         |
| OCaml (toplevel)         | 54.76 s    | 5.9 GB    |                                                         |
| Java 8 (w/o generics)    | 57.67 s    | 6.2 GB    | OpenJDK implementation                                  |
| Java 8 (w/ lambdas)      | 1m 13 s    | 6.6 GB    | OpenJDK implementation                                  |
| Java 8 (w/ OOP)          | 1m 27 s    | 8.8 GB    | OpenJDK implementation                                  |
| js (Firefox 109.0)       | (29.93 s)  | -         | Crash with "out of memory"                              |
| js (node v18)            | (53.48 s)  | 6.2 GB    | Crash with "JavaScript heap out of memory"              |
| js (node v12)            | (1m 57 s)  | 3.8 GB    | Crash with "JavaScript heap out of memory"              |
| Python 3                 | (2m 39 s)  | 15 GB     | Crash with "Killed" (swap used)                         |


#### Partial benchmark results (only char and int vectors):

| Language                 | Time       | Max RAM   | Comment                                                 |
| :----------------------- | :--------: | :-------: | :------------------------------------------------------ |
| js (node v12)            | 6.649 s    | 2.7 GB    |                                                         |
| js (node v18)            | 7.484 s    | 4.3 GB    |                                                         |
| js (Firefox 109.0)       | 12.86 s    | -         |                                                         |
| Python 3                 | 1m 15 s    | 4.0 GB    |                                                         |
