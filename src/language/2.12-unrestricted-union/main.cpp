#include <iostream>
#include <complex>
#include <cstdint>

/*!
 * Use case 1: type conversion. Already in this simple example there is a pitfall related
 * to the endianess of the underlying architecture: depending on the endianess e.g. the
 * alpha value is either the most or least significant byte in value. But my using a
 * union this fact is somewhat "hidden".
 */
union Color
{
    // ATTENTION: Endianess of the CPU is affecting the order of the ARGB order in memory here!
    std::uint32_t value;
    struct Argb
    {
        std::uint8_t blue;
        std::uint8_t green;
        std::uint8_t red;
        std::uint8_t alpha;
    } argb;
};

/*!
 * A somewhat less error-prone alternative to the above Color conversion is using a struct,
 * with explicit access member methods. While endianess is still important here this issue
 * becomes more obvious my explicitly having to shift the masked byte by the corresponding
 * number of bits.
 *
 * Note that the goal here is not to provide a solution which works on any endianess, but
 * to simply illustrate the use cases of unrestricted unions and their alternatives. So
 * the below implemenation only works as expected on little endian machines.
 */
struct Color2
{
    std::uint32_t value;
    inline std::uint8_t alpha() const {
        return (value & 0xff000000) >> 24;
    }
    inline std::uint8_t red() const {
        return (value & 0x00ff0000) >> 16;
    }
    inline std::uint8_t green() const {
        return (value & 0x0000ff00) >> 8;
    }
    inline std::uint8_t blue() const {
        return (value & 0x000000ff) >> 0;
    }
};

/*!
 * Use case 2: memory-friendly variant. Note that such an implementation requires the constant use of
 * switch-statements, as shown below in the usage of this Variant.
 *
 * Alternatives are to use type inheritance, templates or - since C++17 - the std::variant.
 */
struct Variant
{
    enum struct Type
    {
        Integer,
        Double,
        String,
        Complex
    };
    Type type;
    // Note: the book omits quite some details, for instance there is no actual member
    //       variable 'value' declared in the book's example. Without it we would
    //       simply have declared the union type. In fact, when declaring a member variable
    //       'value' we get all sorts of compiler errors, which come exactly from the fact
    //       that special functions such as constructors and destructors are deleted
    //       Also refer to the "tagged union" example here:
    //       https://stackoverflow.com/questions/3521914/why-compiler-doesnt-allow-stdstring-inside-union
//    union {
//        int intValue;
//        double doubleValue;
//        std::string stringValue;
//        std::complex<float> complexValue
//    } value;
};


int main(int argc, char *argv[])
{
    Color color {0xffcc11ee};

    // Use case 1
    std::cout << "Color (ARGB): " << std::hex << color.value
              << " alpha: " << static_cast<std::uint32_t>(color.argb.alpha)
              << " red: " << static_cast<std::uint32_t>(color.argb.red)
              << " green: " << static_cast<std::uint32_t>(color.argb.green)
              << " blue: " << static_cast<std::uint32_t>(color.argb.blue) <<  std::endl;

    Color2 color2 {0xffcc11ee};

    std::cout << "Color 2 (ARGB): " << std::hex << color2.value
              << " alpha: " << static_cast<std::uint32_t>(color2.alpha())
              << " red: " << static_cast<std::uint32_t>(color2.red())
              << " green: " << static_cast<std::uint32_t>(color2.green())
              << " blue: " << static_cast<std::uint32_t>(color2.blue()) <<  std::endl;

    // Use case 2
    Variant variant;
    // Refer to comments above
    // variant.value.intValue = 42.0;

    // Use case 3
    // Memory-alignment via unions is better replaced with declaration "alignas"

    return 0;
}
