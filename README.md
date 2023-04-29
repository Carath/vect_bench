# Vectors implementation benchmark

*This is a collection of benchmarks in several languages, aiming to test the implementation of vector libraries.*

The benchmark consists in using vectors (i.e dynamic arrays) which are grown by adding a large number of values (here 100 000 000) one at a time, followed by a quick pass on the vectors values in order to compute a checksum (and make sure the memory has been allocated), and finally remove each value one by one. The goal is to measure how fast the vector underlying array can realloc itself, and comes from the need of quickly growing a data structure while still allowing random access, as is seen with some implementations of priority queues.

Additionally, different types of elements are used to fill the vectors (element size of 8, 32 and 128 bits) in order to both benchmark the implementation speed in different settings and display the use of generics if the language allows to do so. The peak RAM usage here should be around 2 GB, but this depends on implementations (e.g Java needs up to 8 GB).


## Results

Full benchmark results (char, int and 16-byte struct vectors):

| Language                 | Time       | Max RAM   | Comment                                                 |
| :----------------------- | :--------: | :-------: | :------------------------------------------------------ |
| C (clang 10.0.0)         | 1.309 s    | 1.6 GB    | Homemade vectors and generics (v1.1).                   |
| Rust (release + asm)     | 1.328 s    | 1.6 GB    | Assembly is only emitted along with the target.         |
| Rust (release)           | 1.528 s    | 1.6 GB    |                                                         |
| C (gcc 9.4.0)            | 2.104 s    | 1.6 GB    | Homemade vectors and generics (v1.1).                   |
| cpp (clang++ 10.0.0)     | 2.665 s    | 2.1 GB    |                                                         |
| cpp (g++ 9.4.0)          | 3.000 s    | 2.1 GB    |                                                         |
| go                       | 3.489 s    | 7.6 GB    | PGO didn't bring any noticeable improvement.            |
| Ada                      | 4.076 s    | 2.1 GB    |                                                         |
| Nim (arc GC)             | 7.077 s    | 6.4 GB    |                                                         |
| v (prod)                 | 7.630 s    | 4.9 GB    | Compiling is very slow in production mode.              |
| Nim (default GC)         | 9.845 s    | 7.6 GB    |                                                         |
| v                        | 20.20 s    | 5.4 GB    |                                                         |
| Java 8 (w/o generics)    | 57.67 s    | 6.2 GB    |                                                         |
| Java 8 (w/ lambdas)      | 1m 13 s    | 6.6 GB    |                                                         |
| Java 8 (w/ OOP)          | 1m 27 s    | 8.8 GB    |                                                         |
| js (Firefox 109.0)       | (29.93 s)  | -         | Crash with "out of memory"                              |
| js (node v18)            | (53.48 s)  | 6.2 GB    | Crash with "JavaScript heap out of memory"              |
| js (node v12)            | (1m 57 s)  | 3.8 GB    | Crash with "JavaScript heap out of memory"              |
| Python 3                 | (2m 39 s)  | 15 GB     | Crash with "Killed" (swap used)                         |

Partial benchmark results (only char and int vectors):

| Language                 | Time       | Max RAM   | Comment                                                 |
| :----------------------- | :--------: | :-------: | :------------------------------------------------------ |
| js (node v12)            | 6.649 s    | 2.7 GB    |                                                         |
| js (node v18)            | 7.484 s    | 4.3 GB    |                                                         |
| js (Firefox 109.0)       | 12.86 s    | -         |                                                         |
| Python 3                 | 1m 15 s    | 4.0 GB    |                                                         |

Notes:
- Reported RAM values are the maximum RAM peak found across several runs.
- Most measurements here have been done using the provided ``` benchmark.sh ``` script. Run ``` sh benchmark.sh -help ``` to see details about its usage, options and features. A basic use here would be ``` sh benchmark.sh C/test.exe ```
- If one so desire to not use the previous script, the ``` time ``` command available on Linux systems can be used for time measurements. To measure the RAM usage, use ``` /bin/time -v ``` instead.
- Results shown above come from tests done on an Intel i5-7300HQ 2.50GHz CPU, on Ubuntu 20.04.


## Installation

Two main installation methods are given: one specific to Ubuntu, the other more universal using [Docker](https://docs.docker.com/engine/install).

### Without Docker

Simply run on an Ubuntu system: ``` sudo sh install.sh ``` and *voilà*.

### Using Docker

The benchmarking environment can easily be deployed on any system with Docker installed. The resulting image should build in approximately 7 minutes, and should weight around 3.5 GB.

Notes:
- The commands below may need to be run with root privilege.
- For a better isolation, no Docker volume is mounted, therefore make sure to rebuild the image with each code change.
- An editor may be installed in the docker image (see Dockerfile) if one does not want to use ``` docker cp ```.

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
