# Strongly-Typed (Scoped) Enumerations

## About
Enumerations with keyword struct (or class) are strongly typed, need to
be accessed with their fully qualified name and cannot accidentally be
converted to their underlying type (typically int).

## Why
Traditional enumerations (without keyword struct or class) "pollute" the
global namespace. Conversion errors with int may also easily happen.

## How to use
_enum structs_ and _enum classes_ are simply better. By choosing a smaller
underlying type (such as _uint8_t_) a bit of memory may even be saved. Note
that larger types than int do not need to be manually defined: the compiler
chooses larger underlying types as needed.

_enum struct_ and _enum class_ are technically the same. However since
fields are public by default for _structs_ choosing _enum struct_ feels
more natural.

## Since
C++11
