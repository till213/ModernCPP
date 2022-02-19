# Call Constructor From Constructor

## About
A constructor may delegate part of the class initialisation to another constructor, by simply
calling that other constructor.

## Why
Instead of calling a common "initialise" function calling another constructor is cleaner and
still profits from direct member initialisation.

As a side effect: once the first constructor is finished the class is "completely initialised"
(except the additional member variables), which means that when deriving from a base class
and calling its base constructor the current constructor may then already call virtual methods
(which is possible as soon as at least one constructor has been fully completed).

## How to use
Having lots of different constructors may be confusing and constructors may call each other if
one does not pay attention. To prevent just this good practice is that constructors with less
arguments (only) call those constructors with more arguments (by providing default values).

## Since
C++11
