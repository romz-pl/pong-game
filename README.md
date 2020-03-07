# Implementation in C++ the clasic pong game based on SDL library

1. More about Pong game can be found on [wiki pages](https://en.wikipedia.org/wiki/Pong)

2. The implematation is based on one provided in the Sanjay Madhav's book "Game Programming in C++", see the related [repository](https://github.com/gameprogcpp/code)

3. The impelemtation is based on [SDL library](https://www.libsdl.org/) 

4. The project uses [cmake](https://cmake.org/) configuration files, and hence is platform independent.

5. In order to build the project make the following steps:
    - clon this git repository into `pong` directory
    - create build directory outside the cloned source directory
    - type: `cd build && cmake ../pong && make`
    - in order to start the game use `build/src/pong` binary file
