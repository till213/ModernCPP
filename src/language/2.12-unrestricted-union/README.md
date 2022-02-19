# Unrestricted Union

## About
Unions may now also contain elements with special element functions. For instance the following is now possible:

```
class Foo
{
public:
    Foo()
        : m_value(3)
    {}
private:
    int m_value;
};

union Bar
{
    int a;                 // This has always been possible
    std::string b;         // Not possible until now
    std::complex<float> c; // Not possible until now
    Foo f;                 // Not possible until now
```

## Why
Objects with special element functions such as constructors or assignment operators were not possible in unions until now. Neither were objects allowed with virtual methods, references as members or base classes.

The reason is obvious: at runtime it isn't possible to tell what the actual value of the union should be. So when creating the above union Bar: which constructor should be called? The one of std::string, std::complex or Foo? Or all of them or none?

The solution is now simple: all those special functions are simply deleted (also refer to [Delete And Restore Automatic Implementations](../2.9-auto-impl/README.md).

## How to use
Unions are always to be used with care. After all one needs to know at runtime what kind of data (object) a union contains at any given time. And how much are objects like std::string or std::complex worth without their constructors anyway?

Here is a list of the typical usage scenarios for unions:

- Type conversion
- Memory-friendly implemenation of variants
- Memory alignment

In short: better try to avoid unions. In most cases there are less error-prone alternatives. In "close to the hardware"-development scenarios - e.g. for memory-alignment - one probably also does not need objects with special functions.

## Since
C++11
