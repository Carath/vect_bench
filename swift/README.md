# Swift basics


## Useful links

- <https://www.swift.org/about/>
- <https://docs.swift.org/swift-book>


## Installation

Follow the instructions found [here](https://www.swift.org/server/guides/deploying/ubuntu.html), or refer to the relevant part of the global installation script ``` ../install.sh ```.

To check the installed version (here ``` 5.8 ```):

```sh
swift --version
```


## Compiling and running

Create a new project with:

```sh
swift package init --type executable
```

Compile in debug mode:

```sh
swift build
```

The executable will be saved in ``` .build/x86_64-unknown-linux-gnu/debug/ ```.

To compile and run as the same time, use instead:

```sh
swift run
```

To compile with optimizations on, run:

```sh
swift build -c release
```

The executable will then be created in ``` .build/x86_64-unknown-linux-gnu/release/ ```.
