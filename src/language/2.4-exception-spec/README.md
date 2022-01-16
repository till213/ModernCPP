# Exception specification

## About
The previous _throw_ specification has been deprecated and mostly replaced
by the new _noexcept_ specification, which specifies that a function does
not throw any exception.

## Why
_Throw_ was used to declare which exceptions would be thrown by a given
function. However compilers cannot verify this claim at compile time, which 
in the end lead to less stable programs.

However being able to specify exceptions is still interesting, so _noexcept_
has been introduced: if a _noexcept_ function throws an exception, the
application is still immediately terminated, but it keepts the programmer
from having to figure out exactly which exceptions are allowed to be thrown.

An extension also exists for templates where an argument indicates whether
the specification holds true or not.

## How to use
Using _noexcept_ both documents the intention of a function and allows
the compiler to optimise code.

In combination with templates its usage seems rather complicated though,
compared with the advantages.

## Since
C++11
