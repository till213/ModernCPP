# Rvalue references

## About
An _rvalue_ reference can only point to an unnamed (anonymous) object.

For instance the following function cannot be called with normal _string_ instances:

```
void foo(std::string &&s)
{
  ...
}
```

However calling it with a temporary is allowed:
```
foo(std::string("Foo"));
```

Since nameless instances cannot be accessed after use they may be destroyed by the function.
This allows to implement more efficient functions with _move_ semantics.

## Why
Rvalues allow to implement functions with _move_ semantics where ownership of the instance
is moved.

## How to use
Rvalues are declared with &&. Depending on whether a function is called with an _rvalue_ or
_lvalue_ reference the compiler chooses the proper implementation.

## Since
C++11

## More
[thbecker.net: Rvalue references](http://thbecker.net/articles/rvalue_references/section_01.html)
