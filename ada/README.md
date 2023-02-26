# Ada

## Links

- https://en.wikibooks.org/wiki/Ada_Programming#Getting_Started
- https://docs.adacore.com/gnat_ugn-docs/html/gnat_ugn/gnat_ugn.html
- https://learn.adacore.com/about.html
- https://riptutorial.com/ada
- https://www.adaic.org/resources/add_content/standards/05rm/html/RM-TOC.html


## Installation

```
sudo apt-get install gnat
```


## Compiling

Compiling an .adb file can be done with:

```
gcc -c example.adb
gnatbind example
gnatlink example
```

Or more simply:

```
gnatmake example.adb
```

Cleaning the produces binaries is done with:

```
gnatclean *
```

Compiling with warnings and optimizations is done with the command below. Note that ``` gnatclean ``` may need to be used if a previous compilation has been done:

```
gnatmake -Wall -O2 example.adb
```


## Usage

Compile this project with:

```
gnatmake -Wall -O2 -D obj src/benchmark.adb
gnatmake -Wall -O2 -D obj src/benchmark_inst.adb
```

Then run the benchmark with ``` ./benchmark_inst ```
