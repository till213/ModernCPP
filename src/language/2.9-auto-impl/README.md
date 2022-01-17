# Delete and create auto implementations

## About
With the new keywords _delete_ and _default_ the (non-)creation of automatic implementations for
constructors and assignment operators etc. can be controlled.

## Why
This is of great help for lazy programmers - so everyone ;) - who do not want to implement boilerplate
code.

## How to use

### Scenario 1 - Remove implicitly generated functions
Use _delete_ when

- the class does not support a "copy" constructor
- the class should not have a "move" constructor (even an automatic implementation would be possible)
- the instance of the class should not be assignable

Or in short: if an automatically generated function would semantically not work correctly or is otherwise
not of use.

Note that there exists a dependency between the various elements, e.g. deleting the copy constructor also
removes all other constructors and assignment operators.

The typical example would look like:

```
class Foo
{
public:
  Foo(const Foo &) = delete;
protected:
  std::string *s_;
};
```

### Scenario 2 - Restore implicitly removed functions
Use _default_ to restore automatically generated functions when

- the class defines a custom constructor (which prevents generation of all default constructors)
- the class explicitly _deletes_ a constructor or assignment operator, in which case all related functions are also removed

### Scenario 3 - Restore a removed base class function
Use _default_ to restore automatically generated functions when

- the base class has explicitly _deleted_ them
- the base class has implemented them

---
**NOTE**

This does not seem to work, at least not on macOS (clang).

---

### Scenario 4- Change specifiers
Use _default_ to change specifiers. Generated functions are typically _public_, _inline_ and not _explicit_, which can be changed
using _default_.

A useful example is to make the automatically generated destructor _virtual_ (which is not the case by default!):

```
class Foo
{
public:
  Foo();
  virtual ~Foo();
  ...
}

// Saves a little bit of typing
Foo::~Foo() = default;
```


## Since
C++11
