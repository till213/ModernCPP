# Prevent override (final methods)

## About
A final class cannot be derived from. A final method cannot be overridden.

## Why
Most "leaf" classes are not designed to be overridden or extended. The new _final_ keyword
helps to clearly specify the class contract (API), to prevent (accidental) misuse.

## How to use
The new _final_ should always be used when a class or method is not meant to be extended or overridden.

## Since
C++11
