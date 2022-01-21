#include <string>
#include <memory>

class Foo
{
public:
    /*!
     * A custom constructor prevents the automatic creation
     * of the other default constructors.
     */
    Foo(int i)
    {}

    /*!
     * However we can restore the automatically generated default
     * constructor.
     */
    Foo() = default;

    /*!
     * We can also remove the automatically created assignment operator.
     */
    Foo &operator=(const Foo &src) = delete;
};

/*!
 * Scenario 1 - prevent copying of a class.
 */
class NonCopyable
{
public:
    NonCopyable()
        : s_(std::make_unique<std::string>())
    {}

    NonCopyable(const NonCopyable &) = delete;
protected:
    std::unique_ptr<std::string> s_;
};

/*!
 * Scenario 2 - Restore implicitly removed functions.
 */
class Bar
{
public:
    Bar()
        : s_(std::make_unique<std::string>())
    {}

    /*!
     * Restore the _move_ constructor.
     */
    Bar(Bar &&) = default;

private:
    std::unique_ptr<std::string> s_;
};

/*!
 * Scenario 3 - Restore functions which have been _deleted_ in
 * the base class.
 */
class Base
{
public:
    Base() = delete;
    Base &operator=(const Base&) = delete;
};

class Derived : public Base
{
public:
    // IMPLEMENTATION NOTE: This actually does not work, at least
    // not on macOS (clang). Here we get a warning:
    // "explicitly defaulted default constructor is implicitly deleted"
    // Note: because base class 'Base' has a deleted default constructor
    Derived() = default;
    // Same warning for the default assignment operator
    Derived &operator=(const Derived&) = default;
};

/*!
 * Scenario 4 - Change specifiers.
 */
class Special
{
public:
    explicit Special(Special &&);
    virtual ~Special();
protected:
    Special();
};

Special::Special(Special &&) = default;
Special::~Special() = default;
Special::Special() = default;

int main(int, char *[])
{
    NonCopyable n;
    // Compiler error: call to deleted constructor of 'NonCopyable'
    // NonCopyable m(n);

    NonCopyable m;
    // Compiler error: object of type 'NonCopyable' cannot be assigned because
    // its copy assignment operator is implicitly deleted
    // n = m;

    Bar bar {Bar()};

    // IMPLEMENTATION NOTE: This actually does not work, at least
    // not on macOS (clang). Compiler error: "call to implictly-deleted
    // default constructor of 'Derived'".
    // Derived d;

    // Compiler error: the default constructor is now protected
    // Special s;

    return 0;
}
