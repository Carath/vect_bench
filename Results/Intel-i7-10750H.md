# Intel i7-10750H results

Tests done on an Intel i7-10750H @ 2.60 GHz, on Windows 11 under WSL2 (Ubuntu 20.04).

Note: average as well as median times are reported, since this configuration yields to a [long tail distribution](https://en.wikipedia.org/wiki/Long_tail).


#### Full benchmark results (char, int and 16-byte struct vectors):

| Language                 | Average time | Median time | Max RAM   | Comment                                                 |
| :----------------------- | :----------: | :---------: | :-------: | :------------------------------------------------------ |
| C (clang 10.0.0)         | 0.612 s      | 0.594 s     | 1.6 GB    | Homemade vectors and generics (v1.2).                   |
| Rust (release + asm)     | 0.646 s      | 0.632 s     | 1.6 GB    | Assembly is only emitted along with the target.         |
| Rust (release)           | 0.713 s      | 0.703 s     | 1.6 GB    |                                                         |
| C++ (clang++  10.0.0)    | 1.008 s      | 0.925 s     | 2.1 GB    |                                                         |
| C (gcc 9.4.0)            | 1.305 s      | 1.276 s     | 1.6 GB    | Homemade vectors and generics (v1.2).                   |
| C++ (g++ 10.0.0)         | 1.437 s      | 1.283 s     | 2.1 GB    |                                                         |
| Python 3.8.10            | 6m 52 s      | -           | -         | Crash with "Killed"                                     |
