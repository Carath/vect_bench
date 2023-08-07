# Vectors implementation benchmark

*This is a collection of benchmarks in several languages, aiming to test the implementation of vector libraries.*

The benchmark consists in using vectors (i.e dynamic arrays) which are grown by adding a large number of values (here 100 000 000) one at a time, followed by a quick pass on the vectors values in order to compute a checksum (and make sure the memory has been allocated), and finally remove each value one by one. The goal is to measure how fast the vector underlying array can realloc itself, and comes from the need of quickly growing a data structure while still allowing random access, as is seen with some implementations of priority queues.

Additionally, different types of elements are used to fill the vectors (element size of 8, 32 and 128 bits) in order to both benchmark the implementation speed in different settings and display the use of generics if the language allows to do so. The peak RAM usage here should be around 2 GB, but this depends on implementations (some languages need over 8 GB).


## Results

- [Intel i5-7300HQ results](Results/Intel-i5-7300HQ.md)
- [Intel i7-10750H results](Results/Intel-i7-10750H.md)
- [Intel i9-10910 results](Results/Intel-i9-10910.md)
- [Apple M2 Max results](Results/Apple-M2-Max.md)
- [Apple M1 results](Results/Apple-M1.md)

Notes:
- Reported times are the average runtimes obtained from several runs, the median times may also be given if they differ substantially. RAM values are the maximum RAM peak found across those several runs.
- Most measurements here have been done using the provided ``` benchmark.sh ``` script. To see details about its usage, options and features simply run ``` sh benchmark.sh -help ```. A basic use on the C benchmark would be, from the ``` c ``` directory: ``` sh ../benchmark.sh test.exe ```
- If one so desire to not use the previous script, the ``` time ``` command available on Linux systems can be used for time measurements. To measure the RAM usage, use ``` /bin/time -v ``` instead.
- Results shown above come from tests done only on 64-bit systems, so far.
- The number of values added to the vectors are read from file for the C, C++ and Rust benchmarks, in hope to prevent unwanted compiler optimizations.


## Installation

Two main installation methods are given: one specific to Ubuntu, the other more universal using [Docker](https://docs.docker.com/engine/install).

### Without Docker

Simply run on an Ubuntu system: ``` sudo sh install.sh ``` and *voilà*.

### Using Docker

The benchmarking environment can easily be deployed on any system with Docker installed. The resulting image should build in approximately 10 minutes, and should weight around 6 GB.

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


## TODO

Languages to test:
- [C#](https://learn.microsoft.com/en-us/dotnet/core/install/linux-ubuntu-2004) / [Mono](https://www.mono-project.com/)
- [Kotlin](https://kotlinlang.org/docs/command-line.html)
- [Haxe](https://haxe.org/) outputs (in particular the C++ one).
- [Zig](https://en.wikipedia.org/wiki/Zig_(programming_language)) when the language is more mature.
