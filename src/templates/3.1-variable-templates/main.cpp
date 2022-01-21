#include <string>
#include <iostream>

/*! Also variables can now be defined with templates */
template<typename T>
T var;

/*! Probably the archetypical example is to provide constants with different precision. */
template<typename T>
constexpr T Pi = static_cast<T>(3.14159265359);

/*! Another use case is in template specialisation */
template<typename T>
T MaxValue;

template<>
constexpr long MaxValue<long> = 2147483647;

template<>
constexpr short MaxValue<short> = 32767;

std::string formatNumber(long long n) {
    std::string s;
    if (n > MaxValue<long>) {
        s = "long long";
    } else if (n > MaxValue<short>) {
        s = "long";
    } else {
        s = "short";
    }
    return s;
}

int main(int, char *[])
{
    var<int> = 3;
    var<double> = 42.42;
    var<std::string> = "Karl";
    std::cout << var<int> << ", " << var<double> << ", " << var<std::string> << std::endl;

    float circumfencef = 2.0f * 7.1f * Pi<float>;
    double circumfenced = 2.0f * 7.1f * Pi<double>;
    std::cout << "Circumfence (float): " << circumfencef << ", circumfence (double): " << circumfenced << std::endl;

    std::cout << formatNumber(2147483648) << ", " << formatNumber(2147483647) << ", " << formatNumber(32767) << std::endl;

    return 0;
}
