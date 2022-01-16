# Attributes

## About

Attributes allow to give the compiler additional hints.

## Why

Attributes standardise some of the already existing compiler-specific
attributes.

Attributes may be assigned to literally all language elements such as
types, variables, functions, names, code blocks, modules, namespaces
and enumerations.

The following attributes are defined:

| Attribute             | Meaning                                                                 |
|-----------------------|-------------------------------------------------------------------------|
| noreturn              | Function never returns                                                  |
| carries_dependency    | Behaviour of function related to memory access order                    |
| deprecated
| deprecated("message") | Type, function etc. shall not be used anymore; compiler creates warning |
| fallthrough           | No compiler warning for label fallthrough                               |
| nodiscard             | Warning when type, enumeration or function is used in an expression 
                          whose result is discarded                                               |
| maybe_unused          | No warning if object is not being used                                  |

## How to use

Attributes help to supress compiler warnings, document the code and make intentions of the programmer explicit.

## Since
C++11 (attributes in general)
C++14 (deprecated)
C++17 (fallthrough, nodiscard, maybe_unused, namespaces and enumerations
