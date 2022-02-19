# Inherit Constructors

## About
With the following using statement

```
class Derived : public Base
{
    using Base::Base  
};

the Derived class inherits all constructors as defined in the Base class.

## Why
Before C++11 each desired contructor had to be redefined in the Derived class.

## How to use
This feature essentially only saves a bit of typing. It only makes sense if the Derived
class does not have any additional member variables - otherwise they would remain
uninitialised when calling the inherited contructors!

So besides creating new pitfalls (uninitialised member variables) this feature is
only useful in a few selected cases.

## Since
C++11
