# Rust basics


## Useful links:

- https://doc.rust-lang.org/std/index.html
- https://doc.rust-lang.org/reference/introduction.html
- https://www.rust-lang.org/learn/get-started


## Installation

For Linux (Ubuntu) run the following:

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

To check the installed versions:

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

``` cargo new rust ```

Building the project:

``` cargo build ```

Note that executables will be created in ``` target/release/ ```. Also, by default the code isn't optimized. To change that, use instead:

``` cargo build --release ```

To run an unoptimized project use ``` cargo run ```, and ``` cargo run --release ``` for the optimized version.
Note that the ``` cargo run ``` command will build the project if needed, making the ``` cargo build ``` step unnecessary.

Finally, to remove the generated ``` target/ ``` directory use:

``` cargo clean ```


## Expert stuff

By default rust programs are compiled by cargo statically, therefore parts of the std lib will be included in the executable, resulting in (somewhat) large files (a few MB). To prevent this, one can compile dynamically and specify the path of the shared lib (here ``` libstd-2a15b3cd0948397b.so ```):

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




-----------

https://medium.com/journey-to-rust/viewing-assembly-for-rust-function-d4870baad941
https://stackoverflow.com/questions/39219961/how-to-get-assembly-output-from-building-with-cargo
https://github.com/Manishearth/rust-clippy

-----------

use rustc alone?

Compile a source file with some optimization on:



rustc -O src/main.rs
rustc -C debuginfo=0 -C opt-level=3 src/main.rs
rustc -C debuginfo=0 -C opt-level=3 --emit asm src/main.rs

-----------

Faster !!!??? Only with Cargo, emitting asm only with rustc does not change the executable.

Yield an executable of 384 bytes (resp. 344) less than before with static (resp. dynamic) build.

cargo rustc --release -- --emit asm

RUSTFLAGS="--emit asm" cargo build --release

RUSTFLAGS="--emit asm -C prefer-dynamic -C link-arg=-Wl,-rpath=/home/mypc/.rustup/toolchains/stable-x86_64-unknown-linux-gnu/lib" \
  cargo build --release

-----------

cargo install cargo-asm

cargo asm --asm-style=intel test::main

If the "bench" is not inlined (e.g using ``` #[inline(never)] ```) then the assembly of its monomorphized versions may be seen with:

cargo asm --asm-style=intel test::bench

But does this uses the release mode? Doesn't seem so...

-----------
