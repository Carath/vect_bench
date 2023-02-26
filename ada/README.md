# Ada

Links (to cleanup):

- https://en.wikibooks.org/wiki/Ada_Programming#About_Ada
- https://gcc.gnu.org/onlinedocs/gcc-4.6.4/gnat_ugn_unw/Running-a-Simple-Ada-Program.html
- https://docs.adacore.com/gnat_ugn-docs/html/gnat_ugn/gnat_ugn/gnat_and_program_execution.html
- https://learn.adacore.com/about.html
- https://learn.adacore.com/courses/Ada_For_The_Embedded_C_Developer/chapters/08_Performance.html
- https://learn.adacore.com/courses/Ada_For_The_CPP_Java_Developer/index.html
- https://en.wikibooks.org/wiki/Ada_Programming/All_Operators
- https://www.adaic.org/resources/add_content/standards/05rm/html/RM-A-18-2.html
- https://learn.adacore.com/courses/intro-to-ada/chapters/standard_library_containers.html
- https://riptutorial.com/ada
- https://franckbehaghel.eu/programming/ada/ada-vertors/ada-vectors-programming.php
- https://zestedesavoir.com/tutoriels/645/apprenez-a-programmer-avec-ada/
- https://en.wikibooks.org/wiki/Ada_Programming/Generics

- https://stackoverflow.com/questions/17064479/defining-a-modular-type-within-a-generic-package
- https://learn.adacore.com/courses/intro-to-ada/chapters/generics.html
- https://en.wikibooks.org/wiki/Ada_Programming/Generics


## Installation

```
sudo apt-get install gnat
```


## Compiling

Compile with:

```
gcc -c benchmark.adb
gnatbind hello
gnatlink hello
```

Or more simply:

```
gnatmake benchmark.adb
```

Cleaning the produces binaries is done with:

```
gnatclean benchmark
```

Compiling with optimizations is done with the command below. Note that ``` gnatclean ``` may need to be used if a previous compilation has been done:

```
gnatmake -Wall -O2 benchmark.adb
```

Compiling the generic version:

```
gnatmake -Wall -O2 benchmark.adb
gnatmake -Wall -O2 benchmark_inst.adb
```
