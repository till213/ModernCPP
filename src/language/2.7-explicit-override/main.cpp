#include <iostream>
#include <memory>

class Base
{
public:
    virtual void foo()
    {
        std::cout << "Base::foo called" << std::endl;
    }
};

class Extension : public Base
{
public:
    /*!
     * By marking this method as _override_ the compiler is able to verify
     * the implementation override.
     */
    virtual void foo() override
    {
        std::cout << "Extension::foo called" << std::endl;
    }
};

int main(int, char *[])
{
    std::unique_ptr<Base> b = std::make_unique<Base>();
    b->foo();
    b = std::make_unique<Extension>();
    b->foo();
    return 0;
}
