# Build Instructions

## Prerequisites

* A C++17 compiler
* CMake

## Linux / macOS

```
cd ModernCPP
make
```

* The binaries will be in the _build/bin_ subdirectory
* The provided Makefile will simply trigger the build by invoking CMake in the created _build_ subdirectory

## Windows

The easiest method for me is to simply install Qt + Qt Creator ([download](https://www.qt.io/download)) which comes with all required compilers (MinGW + gcc) and tools (cmake + ninja). Next:

* Open Qt Creator
* "File/Open file or project...", select the _CMakeLists.txt_ (in the top-level project directory)
* Hit CTRL + B ("build")

Note that compiling with Qt Creator is pure convencience, as the example code has no dependency on Qt whatsoever. In fact, any other environment which provides CMake (make is optional) and a C++17 compiler on Windows will do.

## Compiler Warnings

Note that certain compiler warnings are deliberate, specifically those which illustrate the use
of the new [[[deprecated]]](./src/language/2.5-attributes/README.md) attribute.

On the other hand certain compilers / code analysers (Apple clang specifically) generate warnings or even generate errors for C++17 features such as [restoring deleted default constructors](./src/language/2.9-auto-impl/README.md) or [calling constructors from constructors](./src/language/2.10-ctor-from-ctor/README.md). According to the book those C++17 features should work. I left those examples in and annotated them accordingly (or even had to comment them out completely, such that the code compiles in the first place), for reference.

If on the other hand you encounter other kind of warnings - or even compilation errors - feel free to raise an issue here on github.com :)
