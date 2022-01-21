#include <type_traits>
#include <iostream>

class Foo
{
public:
    /*!
     * The noexcept specification replaces the now obsolete _throws_ specification.
     */
    int calculate() noexcept
    {
        return 42;
    }

    /*!
     * This method may still throw any exceptions.
     */
    int retrieve()
    {
        return 1001;
    }
};

/*! This function does not throw any exceptions. */
int doBar(int arg) noexcept {
    return arg;
}

/*!
 * An extension exists for templates where the boolean argument
 * defines whether the _noexcept_ specification holds or not, e.g.
 * depending on the template type.
 */
template<typename T>
void doSomething([[maybe_unused]]T a, [[maybe_unused]]T b) noexcept(std::is_trivial<T>::value)
{
    // Do something meaningful
}

/*!
 * The _noexcept_ argument may also be derived from the specification
 * of a given method. In this example doCalculate must not throw
 * any exceptions, as per the specification of calculate().
 */
template<typename T>
int doCalculate(T a) noexcept(noexcept(a.calculate()))
{
    return a.calculate();
}

/*!
 * In this example exceptions may be thrown, as per the specification
 * of retrieve().
 */
template<typename T>
int doRetrieve(T a) noexcept(noexcept(a.retrieve()))
{
    return a.retrieve();
}

int main(int, char *[])
{
    // Returns true, as doBar is specified with noexcept
    bool isNoThrowInvocable = std::is_nothrow_invocable_v<decltype(doBar), int>;
    std::cout << "doBar nothrow invocable: " << isNoThrowInvocable << std::endl;

    // Returns true, as int is a trivial type
    isNoThrowInvocable = std::is_nothrow_invocable_v<decltype(doSomething<int>), int, int>;
    std::cout << "doSomething<int> nothrow invocable: " << isNoThrowInvocable << std::endl;

    // Returns false, as Foo is a non-trivial type
    isNoThrowInvocable = std::is_nothrow_invocable_v<decltype(doSomething<Foo>), int, int>;
    std::cout << "doSomething<Foo> nothrow invocable: " << isNoThrowInvocable << std::endl;

    // Returns true, as the called Foo::calculate is specified with noexcept
    isNoThrowInvocable = std::is_nothrow_invocable_v<decltype(doCalculate<Foo>), Foo>;
    std::cout << "doCalculate nothrow invocable: " << isNoThrowInvocable << std::endl;

    // Returns false, as the called Foo::retrieve is not specified with noexcept
    isNoThrowInvocable = std::is_nothrow_invocable_v<decltype(doRetrieve<Foo>), Foo>;
    std::cout << "doRetrieve nothrow invocable: " << isNoThrowInvocable << std::endl;

    return 0;
}
