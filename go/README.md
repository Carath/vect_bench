# Basics of go (golang)


## Installing

Follow the link instructions: <https://go.dev/doc/install>

To check the installed version (here ``` go1.20 ```) simply run: ``` go version ```


## Documentation

- <https://go.dev/doc/>
- <https://go.dev/tour/basics/1>
- <https://go.dev/tour/methods/1>
- <https://gobyexample.com/>
- <https://go.dev/blog/pgo-preview>


## Buiding and running code

```sh
go build
./bench
```


## Using PGO

To use profile-guided optimization (PGO), run the following command:

```sh
go test -cpuprofile cpu.prof -memprofile mem.prof -bench=. -count=3
```

Then rebuild the project using one of the generated ``` .prof ``` file, e.g ``` go build -pgo=cpu.prof ```

Here PGO didn't bring any noticeable improvement.
