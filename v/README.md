# Basics of v (vlang)


## Documentation

- <https://github.com/vlang/v/blob/master/doc/docs.md>
- <https://modules.vlang.io/>


## Installing

Follow the instructions found here: <https://github.com/vlang/v>, or run the following commands from the project root directory:

```sh
mkdir -p install && cd install
git clone --depth 1 https://github.com/vlang/v && cd v && make && cd ..
```

To check the installed version, just run the v executable from the installation directory (here ``` ../install/v/ ```):

```sh
../install/v/v
```

Current version: ``` V 0.3.3 b6ecd63 ```


## Building and running code

```sh
../install/v/v test.v
./test
```

To enable optimizations, compile instead in production mode with the following command. Note that compilation becomes *really* slow (~ 5 sec):

```sh
../install/v/v -prod test.v
```
