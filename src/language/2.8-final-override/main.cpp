#include <iostream>
#include <memory>

class Base
{
public:
    virtual void process()
    {
        std::cout << "Base::process called" << std::endl;
    }
};

class Extension : public Base
{
public:
    /*!
     * By marking this method as _final_ it cannot be overridden
     * in extension classes, ensuring that the pre-process and
     * post-process steps are always done.
     */
    virtual void process() override final
    {
        std::cout << "Extension::foo called" << std::endl;
        preProcess();
        doProcess();
        postProcess();
    }
protected:
    virtual void doProcess()
    {
        std::cout << "Extension::doProcess called" << std::endl;
    }
private:
    void preProcess()
    {
        std::cout << "Extension::preProcess called" << std::endl;
    }
    void postProcess()
    {
        std::cout << "Extension::postProcess called" << std::endl;
    }
};

int main(int, char *[])
{
    std::unique_ptr<Base> b = std::make_unique<Extension>();
    b->process();
    return 0;
}
