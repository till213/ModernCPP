#include <iostream>
#include <memory>

class Base
{
public:
    Base(int a, int b, int c)
        : m_a(a), m_b(b), m_c(c), m_d(1001)
    {}

    /*!
     * One constructor may call another constructor. As a good practice
     * constructors with fewer parameters should call those with more
     * parameters, in order to avoid confusion and possibly even mutual
     * dependency (endless recursion of constructor calls).
     */
    Base(int a, int b)
        : Base(a, b, 42)
    {}

    // Note that the compiler expects a constructor call to completely
    // initialise the object, so a mix with other direct initialisers
    // is not possible. So the following would not compile:
    // "an initializer for a delegating constructor must appear alone"
//    Base(int a, int b)
//        : Base(a, b, 42), d_(42)
//    {}

    virtual ~Base() = default;

protected:
    virtual void someMethod()
    {
        std::cout << "Base::someMethod called." << std::endl;
    }

private:
    int m_a;
    int m_b;
    int m_c;
    int m_d;
};

class Derived : public Base
{
public:
    /*!
     * We may also call the base class constructor.
     */
    Derived(int a, int b)
        : Base(a, b)
    {
        // As soon as one constructor has been completed - here: Base() - we
        // may start to call virtual methods. Even in this constructor here.
        // Note: some code analysers such as the clang-analyzer may still complain that a
        //       "call to virtual method during construction bypasses virtual dispatch".
        //       However the proper Derived::someMethod() method is still being called.
        //
        //       Whether that is good practice is another question then.
        someMethod();
    }

protected:
    virtual void someMethod() override
    {
        std::cout << "Derived::someMethod called." << std::endl;
    }
};

int main(int, char *[])
{
    std::unique_ptr<Base> d = std::make_unique<Derived>(1, 2);
    return 0;
}
