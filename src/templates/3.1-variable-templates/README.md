# Templates for variables

## About

Templates may now also be specified for variables (in addition to
classes and functions).

```
template<typename T>
T var
```


## Why

The goal is to implement parametrisable constants.

## How to use

The possibilities for this feature are relatively rare: the prime
example is the definition of the constant pi with different precision
types (float, double).

## Since
C++14
