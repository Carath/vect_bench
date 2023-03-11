# Basics of v (vlang)


## Documentation

- <https://github.com/vlang/v/blob/master/doc/docs.md>
- <https://modules.vlang.io/>


## Installing

Follow the instructions found here: <https://github.com/vlang/v>

To check the installed version, just run the v executable from the installation directory (here ``` ~/git/v/ ```):

```sh
~/git/v/v
```

Current version: ``` V 0.3.3 b6ecd63 ```


## Building and running code

```sh
~/git/v/v test.v
./test
```

To enable optimizations, compile instead in production mode with the following command. Note that compilation becomes *really* slow (~ 5 sec):

```sh
~/git/v/v -prod test.v
```
