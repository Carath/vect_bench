# Apple M2 Max results

Tests done on an Apple M2 Max @ 3.50 GHz, on Mac OS.


#### Full benchmark results (char, int and 16-byte struct vectors):

| Language                 | Time       | Max RAM   | Comment                                                 |
| :----------------------- | :--------: | :-------: | :------------------------------------------------------ |
| Rust (release)           | 0.41 s     |           |                                                         |
| C (clang 14.0.3)         | 0.43 s     |           | Homemade vectors and generics (v1.2).                   |
| C++ (clang++ 14.0.3)     | 0.47 s     |           |                                                         |
| Swift                    | 0.701 s    |           | Runtime checks disabled.                                |
| Swift                    | 0.788 s    |           |                                                         |
| Python 3.9.6             | 2m 01 s    |           | Terminated successfully.                                |
