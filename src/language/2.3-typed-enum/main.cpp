#include <cstdint>
#include<type_traits>
#include <iostream>

/*! The base type - here: uint8_t - may be given. As usual numerical
 *  values may be specified as well
 */
enum struct LineStyle: std::uint8_t
{
    Solid = 0,
    Dotted = 1,
    Dashed = 2
};

/*! We can also forward declare typed enumerations */
enum struct FillStyle: std::uint8_t;

/*!
 * The enumerations are strongly typed: no confusion possible
 * between \c lineStyle and \c fillStyle.
 */
void drawCircle(LineStyle lineStyle, FillStyle fillStyle)
{
    // Draw a nice circle
}

/*! The actual definition follows here */
enum struct FillStyle: std::uint8_t
{
    Solid = 0,
    Hatched = 1,
    Hollow = 2
};

/*! We can define operators (methods in general) for typed enumerations. */
enum struct AggregationFlags: std::uint32_t
{
    Minimum = 0x00000001,
    Maximum = 0x00000002,
    Average = 0x00000004,
    First   = 0x00000008,
    Last    = 0x00000010
};

/*!
 * Here we define the bitwise OR operator for the AggregationFlags.
 */
AggregationFlags operator|(AggregationFlags a, AggregationFlags b)
{
    typedef std::underlying_type<AggregationFlags>::type EnumType;

    return static_cast<AggregationFlags>(static_cast<EnumType>(a) | static_cast<EnumType>(b));
}

int main(int argc, char *argv[])
{
    /*! Typed enumerations must be accessed with their fully qualified name */
    drawCircle(LineStyle::Solid, FillStyle::Hatched);

    AggregationFlags flags { AggregationFlags::Average | AggregationFlags::First };
    std::cout << "Flags: " << static_cast<std::underlying_type<AggregationFlags>::type>(flags) << std::endl;

    return 0;
}
