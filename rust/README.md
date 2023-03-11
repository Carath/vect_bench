# Rust basics


## Useful links

- <https://www.rust-lang.org/learn/get-started>
- <https://doc.rust-lang.org/std/index.html>
- <https://doc.rust-lang.org/reference/introduction.html>
- <https://doc.rust-lang.org/book/title-page.html>
- <https://doc.rust-lang.org/1.9.0/book/README.html>


## Installation

For Linux (Ubuntu) run the following:

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

To check the installed versions (here ``` 1.67.0 ```):

```sh
rustc --version
cargo --version --verbose
rustc --print target-list # list all target architectures
```

See also the ``` ~/.cargo/ ``` and ``` ~/.rustup/ ``` directories.

Moreover, the Rust Programming Language book can be viewed by using:

```sh
rustup docs --book
```


## Basic cargo commands

Creating a project:

```sh
cargo new rust
```

Building the project:

```sh
cargo build
```

Note that executables will be created in ``` target/release/ ```. Also, by default the code isn't optimized. To change that, use instead:

```sh
cargo build --release
```

To run an unoptimized project use ``` cargo run ```, and ``` cargo run --release ``` for the optimized version.
Note that the ``` cargo run ``` command will build the project if needed, making the ``` cargo build ``` step unnecessary.

Finally, to remove the generated ``` target/ ``` directory use: ``` cargo clean ```


## Compiling without cargo

Below are commands to compile a source file with ``` rustc ```, while using optimization flags:

```sh
rustc -O src/main.rs
rustc -C debuginfo=0 -C opt-level=3 src/main.rs
rustc -C debuginfo=0 -C opt-level=3 --emit asm src/main.rs
```


## Expert stuff

### Dynamic builds

By default rust programs are compiled by cargo statically, therefore parts of the standard library will be included in the executable, resulting in (somewhat) large files (a few MB). To prevent this, one can compile dynamically and specify the path of the shared lib (here ``` libstd-2a15b3cd0948397b.so ```):

Method 1:

```sh
cargo rustc --release -- \
  -C prefer-dynamic -C link-arg=-Wl,-rpath=/home/mypc/.rustup/toolchains/stable-x86_64-unknown-linux-gnu/lib
```

Method 2:

```sh
RUSTFLAGS="-C prefer-dynamic -C link-arg=-Wl,-rpath=/home/mypc/.rustup/toolchains/stable-x86_64-unknown-linux-gnu/lib" \
  cargo build --release
```

Note that absolute paths are needed.


### Assembly output

To generate assembly along with the target, append the ``` --emit asm ``` flag while compiling like below (here in release mode):

```sh
cargo rustc --release -- --emit asm
```

Or also with the following command, having the same effect:

```sh
RUSTFLAGS="--emit asm" cargo build --release
```

Note that emitting assembly actually changes the generated target. Here, it somewhat yields a 16% speed gain! Also, this definitely is a cargo thing, since emitting assembly only using rustc does not change the target. Finally, the ``` --emit asm ``` flag can be used with the two commands above for dynamic builds (here with the same speed gain as in the static builds).
