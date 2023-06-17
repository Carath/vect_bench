# Apple M1 results

Tests done on an Apple M1 @ 3.2 GHz, on Mac OS.


#### Full benchmark results (char, int and 16-byte struct vectors):

| Language                 | Time       | Max RAM   | Comment                                                 |
| :----------------------- | :--------: | :-------: | :------------------------------------------------------ |
| C (clang 14.0.3)         | 0.41 s     |           | Homemade vectors and generics (v1.2).                   |
| C++ (clang++ 14.0.3)     | 0.413 s    |           |                                                         |
| Swift (release)          | 0.758 s    |           |                                                         |
| Python 3.9.6             | 2m 13 s    |           | Terminated successfully.                                |
