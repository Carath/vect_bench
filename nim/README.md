# Nim basics


## Useful links:

- https://nim-by-example.github.io/getting_started/
- https://nim-lang.org/docs/tut1.html
- https://nim-lang.org/docs/manual.html
- https://nim-lang.org/docs/nimc.html
- https://nim-by-example.github.io
- https://nim-lang.org/1.4.0/gc.html
- https://narimiran.github.io/nim-basics/


## Installation

For Linux (Ubuntu) run the following:

```sh
curl https://nim-lang.org/choosenim/init.sh -sSf | sh
```

To check the installed version use: ``` nim -v ```

Here: Nim Compiler Version 1.6.10 [Linux: amd64]


## Notes

- Indentation is spaces only (duh).
- ```int ``` type is of arbitrary precision.
- Unusual range behavior:

```nim
for i in 0..n: # goes from 0 to n included !!!
  ...
```


## Compiling


To compile a .nim file (here ``` test.nim ```), use the following:

```sh
nim c test.nim
```

To enable the optimizations, compile with the following (-d:release should be better than -opt:speed):

```sh
nim c -d:release test.nim
```

To use another garbage collector, yielding potential speedups:

```sh
nim c -d:release --gc:arc test.nim
```
