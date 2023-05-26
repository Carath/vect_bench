# OCaml basics


## Useful links

- <https://v2.ocaml.org/manual/index.html>
- <https://v2.ocaml.org/api>
- <https://www2.lib.uchicago.edu/keith/ocaml-class/home.html>
- <https://www.good-eris.net/formation-ocaml/intro.html> (french)


## Installation

```sh
sudo apt-get install ocaml
```

To check the installed version (here ``` 4.08.1 ```), use:

```sh
ocaml -version
```


## Usage

There is three way of running an OCaml program:

### Running with the toplevel interpreter

```sh
ocaml vect.ml
```

### Compiling to bytecode and running the executable

```sh
ocamlc -o exec vect.ml
./exec
```

### Compiling to native code and running the executable

This should yield the faster code:

```sh
ocamlopt -o exec vect.ml
./exec
```


## Remark

To keep the code visually appealing, the 'int' type has been used instead of 'int64'. This requires running the code on a 64-bit machine, otherwise the benchmark results will be irrelevant.
