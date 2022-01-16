/*! This function never returns, as indicated with [[noreturn]]. */
[[noreturn]]
void throwException() {
    throw "An exception";
}

/*! This function is deprecated with [[deprecated]]. */
[[deprecated("Do not use anymore")]]
void foo()
{}

/*! Unused parameters can be annotated with [[maybe_unused]]. */
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    // Generates a compiler warning
    foo();

    int n = 42;
    bool something = true;
    switch (n) {
    case 1:
        // Do something
        break;
    case 2:
        if (something) {
            // Do another thing
            break;
        } else {
            // Note the position of this annotation, which must be technically
            // before the last (empty) statement of a sequence before the new label
            [[fallthrough]];
        }
    case 3:
        // Do the last thing
        break;
    }

    return 0;
}
