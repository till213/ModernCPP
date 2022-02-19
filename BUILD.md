# Build Instructions

## Prerequisites

* A C++17 compiler
* Cmake

## Linux / macOS

```
cd ModernCPP
make
```

* The binaries will be in the _build/bin_ subdirectory
* The provided Makefile will simply trigger the build by invoking cmake in the created _build_ subdirectory

## Compiler Warnings

Note that certain compiler warnings are deliberate, specifically those which illustrate the use
of the new [[[deprecated]]](./src/language/2.5-attributes/README.md) attribute.

On the other hand certain compilers / code analysers (Apple clang specifically) generate warnings or even generate errors for C++17 features such as [restoring deleted default constructors](./src/language/2.9-auto-impl/README.md) or [calling constructors from constructors](./src/language/2.10-ctor-from-ctor/README.md). According to the book those C++17 features should work. I left those examples in and annotated them accordingly (or even had to comment them out completely, such that the code compiles in the first place), for reference.

If on the other hand you encounter other kind of warnings - or even compilation errors - feel free to raise an issue here on github.com :)
