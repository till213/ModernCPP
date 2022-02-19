#include <iostream>
#include <memory>
#include <string>

class Base
{
public:
    explicit Base(int intValue)
        : m_intValue(intValue),
          m_doubleValue(42.0),
          m_stringValue("42")
    {
        std::cout << "Base(int) called." << std::endl;
    }

    explicit Base(double doubleValue)
        : m_intValue(42),
          m_doubleValue(doubleValue),
          m_stringValue("42")
    {
        std::cout << "Base(double) called." << std::endl;
    }

    explicit Base(std::string string)
        : m_intValue(42),
          m_doubleValue(42.0),
          m_stringValue(string)
    {
        std::cout << "Base(string) called." << std::endl;
    }

    virtual ~Base() = default;

    int getIntValue() const noexcept
    {
        return m_intValue;
    }

    double getDoubleValue() const noexcept
    {
        return m_doubleValue;
    }

    std::string getStringValue() const noexcept
    {
        return m_stringValue;
    }

private:
    int m_intValue;
    double m_doubleValue;
    std::string m_stringValue;
};

/*!
 * Inherit the custom constructors from Base. Note that the standard constructor and the default copy
 * constructors are not inherited from Base. Properties like implicit/explicit and public, protected
 * and private are inherited though.
 */
class Derived : public Base
{
    // Constructor inheritance
    // ATTENTION: adding additional member variables here would leave them uninitialised!
    //            Unless we define our own constructors again which somewhat defeats the
    //            advantage of constructor inheritance again
    using Base::Base;

    /*!
     * Unwanted inherited constructors can be deleted.
     */
    Derived(std::string) = delete;
};

int main(int, char *[])
{
    std::unique_ptr d1 = std::make_unique<Derived>(1001);
    std::cout << "d1.intValue: " << d1->getIntValue()
              << " d1.doubleValue: " << d1->getDoubleValue()
              << " d1.stringValue: " << d1->getStringValue() << std::endl;
    std::unique_ptr d2 = std::make_unique<Derived>(3.14159);
    std::cout << "d2.intValue: " << d2->getIntValue()
              << " d2.doubleValue: " << d2->getDoubleValue()
              << " d2.stringValue: " << d2->getStringValue() << std::endl;

    // This would generate an "call to deleted constructor of 'Derived'" error
    //std::unique_ptr d3 = std::make_unique<Derived>("This constructor has been deleted.");
    return 0;
}
