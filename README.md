# Vectors implementation benchmark

*This is a collection of benchmarks in several languages, aiming to test the implementation of vector libraries.*

The benchmark consists in using vectors (i.e dynamic arrays) which are grown by adding a large number of values (here 100000000) one at a time, followed by a quick pass on the vectors values in order to compute a checksum (and make sure the memory has been allocated), and finally remove each value one by one. The goal is to measure how fast the vector underlying array can realloc itself, and comes from the need of quickly growing a data structure while still allowing random access, as is seen with some implementations of priority queues.

Additionally, different types of elements are used to fill the vectors (element size of 8, 32 and 128 bits) in order to both benchmark the implementation speed in different settings and display the use of generics if the language allows to do so. The peak RAM usage here should be around 2 GB, but this depends on implementations (e.g Java needs up to 7 GB).


## Results

Full benchmark results (char, int and 16-byte struct vectors):

| Language                 | Time       | RAM       | Comment                                                 |
| :----------------------- | :--------: | :-------: | :------------------------------------------------------ |
| Rust (release + asm)     | 1.346 s    | 1.5 GB    | Assembly is only emitted along with the target.         |
| Rust (release)           | 1.601 s    | 1.5 GB    |                                                         |
| C                        | 2.016 s    | 1.5 GB    | Homemade vectors and generics.                          |
| cpp                      | 3.090 s    | 2.0 GB    |                                                         |
| go                       | 3.489 s    | 5.3 GB    | PGO didn't bring any noticeable improvement.            |
| Ada                      | 4.076 s    | 2.0 GB    |                                                         |
| Nim (arc GC)             | 7.077 s    | 6.1 GB    |                                                         |
| v (prod)                 | 7.630 s    | 4.6 GB    | Compiling is very slow in production mode.              |
| Nim (default GC)         | 9.845 s    | 7.3 GB    |                                                         |
| v                        | 20.20 s    | 4.9 GB    |                                                         |
| Java 8 (w/o generics)    | 57.67 s    | 5.5 GB    |                                                         |
| Java 8 (w/ lambdas)      | 1m 13 s    | 5.7 GB    |                                                         |
| Java 8 (w/ OOP)          | 1m 27 s    | 7.1 GB    |                                                         |
| js (Firefox)             | (29.93 s)  | -         | Crash with "out of memory"                              |
| js (node v18)            | (53.48 s)  | -         | Crash with "JavaScript heap out of memory"              |
| js (node v12)            | (1m 57 s)  | -         | Crash with "JavaScript heap out of memory"              |
| Python 3                 | (2m 39 s)  | 14 GB     | Crash with "Killed" (swap used)                         |

Partial benchmark results (only char and int vectors):

| Language                 | Time       | RAM       | Comment                                                 |
| :----------------------- | :--------: | :-------: | :------------------------------------------------------ |
| js (node v12)            | 6.649 s    | 2.5 GB    |                                                         |
| js (node v18)            | 7.484 s    | 4.1 GB    |                                                         |
| js (Firefox)             | 12.86 s    | -         |                                                         |
| Python 3                 | 1m 15 s    | 3.8 GB    |                                                         |

Notes:
- Most time measurements here have been done using the ``` time ``` command available on Linux systems. To measure the RAM usage, use ``` /usr/bin/time -v ``` instead.
- Tests have been done on an Intel i5-7300HQ 2.50GHz CPU on Ubuntu 20.04.
- Care has been taken not to include the compile time of the tested targets (e.g for rust using ``` cargo build ``` instead of ``` cargo run ``` and so on).


## Installation

Two main installation methods are given: one specific to Ubuntu, the other more universal using [Docker](https://docs.docker.com/engine/install).

### Without Docker

Simply run on an Ubuntu system: ``` sh install.sh ``` and *voilà*.

### Using Docker

The benchmarking environment can easily be deployed on any system with Docker installed. The resulting image should build in approximately 6 minutes, and should weight around 3 GB.

Notes:
- The commands below may need to be run with root privilege.
- For a better isolation, no Docker volume is mounted, therefore make sure to rebuild the image with each code change.

#### With vanilla Docker

Building the image:

```sh
docker build -t vectors:1.0 .
```

Running a container:

```sh
docker run -it vectors:1.0 /bin/bash
```

#### With Docker Compose

Additionally, one can also use [Docker Compose](https://docs.docker.com/compose/install) if available.

To build the image use:

```sh
docker-compose build
```

Running a container:

```sh
docker-compose run vectors
```

Finally, to remove said container:

```sh
docker-compose down
```


## TODO

- Cleanup the C version code
- C version: does not compile without the -O2 flag !!!
- C version: inline EQ function?
