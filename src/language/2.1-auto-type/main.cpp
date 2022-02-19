#include <vector>
#include <map>
#include <complex>
#include <functional>
#include <iostream>

/*!
 * Since C++14 auto can also be used as a function return value.
 */
auto calculate(double a, int b, float c)
{
    return b / a * c;
}

class Foo {
public:
    const std::string &getName() const {
        return m_name;
    }
    const std::string *getDescription() const {
        return &m_desc;
    }
private:
    std::string m_name {"Mickey Mouse"};
    std::string m_desc {"A funny mouse"};
};

int Func(double, std::string, double) {
    return 42;
}

/*!
 * # About
 * The compiler automatically determines the type of a variable.
 *
 * # How To Use?
 * Some authors (e.g. Meyers 2015) recommend to use auto "whenever possible".
 * However code readability may suffer, especially when using auto as return
 * value.
 *
 * A good compromise is to use auto where the actual type of a variable
 * does not contribute much to the understanding of the code, such as
 * the (technical) type of an iterator itself.
 */
int main(int, char *[])
{
    auto pi = 3.1415;
    std::cout << "Type of pi: " << typeid (pi).name() << std::endl;

    std::string s {"Anthony"};
    auto len = s.length();
    std::cout << "Type of len: " << typeid (len).name() << std::endl;

    std::vector<int> v;
    auto it = v.begin();
    std::cout << "Type of vector iterator: " << typeid (it).name() << std::endl;

    auto res = calculate(42.0, 42, 1001.0f);
    std::cout << "Type of res: " << typeid (res).name() << std::endl;

    // Auto is very useful to omit complitated type declarations for
    // iterators, such as for the following map:
    std::map<std::basic_string<unsigned char>, std::complex<float> (*)(double, double)> functions;
    std::cout << "Type of map iterator: " << typeid (functions.begin()).name() << std::endl;

    // In order to declare the iterator with auto this simply becomes:
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        // Do something here
    }

    // However type derivation does not always work intuitively. Essentially
    // the same rules as for template types are applied, namely:

    // If the initialiser is a reference, then the auto type is the
    // unreferenced type
    Foo foo;
    // The type of name will be std::string, and not const std::string &
    auto name = foo.getName();
    std::cout << "Type of name: " << typeid (name).name() << std::endl;

    // The following declarations are identical, however the second form
    // with an explicit pointer makes it more obvious that the type will
    // be a pointer. However that explicit notation can only be used if
    // the initialiser returns an address.
    auto str_prt1 = foo.getDescription();
    auto *str_ptr2 = foo.getDescription();

    std::cout << "Type of str_prt1: " << typeid (str_prt1).name() << std::endl;
    std::cout << "Type of str_prt2: " << typeid (str_ptr2).name() << std::endl;

    // Further examples where auto may be useful
    auto lambda = [&](double d, const std::string &s) {
        return Func(d, s, d);
    };
    std::cout << "Type of lambda: " << typeid (lambda).name() << std::endl;

    auto f = std::bind(Func, std::placeholders::_1, "Williams", std::placeholders::_2);
    std::cout << "Type of f: " << typeid (f).name() << std::endl;

    std::map<int, std::string> m;
    auto e = m[12];
    std::cout << "Type of e: " << typeid (e).name() << std::endl;

    // But where the type of a variable is not immediately clear from
    // the given initialiser an explicit type declaration may still
    // be preferred, especially if the type is important to understand
    // the subsequent code

    return 0;
}
