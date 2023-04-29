# About


## Installation

Installation: see <https://openjdk.org/install/>

Used openjdk version: ``` 1.8.0_352 ```


## Usage

Compile with:

```sh
javac -d build/ src/*.java
```

To run the benchmark without generics use:

```sh
time java -mx8g -cp build/ BenchNoGenerics
```

To run the benchmark variant with lambda functions use:

```sh
time java -mx8g -cp build/ BenchLambda
```

To run the pure OOP variant use instead:

```sh
time java -mx8g -cp build/ BenchType
```

Note 1: this benchmark uses around 6 GB of RAM, but to be sure an amount of 8 GB has been allowed to the JVM with the ``` -mx8g ``` flag (the default max RAM usage being 4 GB on a 16 GB machine). Also, indications have been given to Java's garbage collector in the hope of freeing some unneeded memory with the instructions below. This generally speeds up the benchmarks a bit.

```java
vect = null; // the now empty vector.
System.gc(); // asking the GC to consider freeing stuff.
```

Note 2: wrapping the *byte* type inside a class yields slower code and more RAM usage than using the *Character* wrapper of the 2-bytes *char* type.
