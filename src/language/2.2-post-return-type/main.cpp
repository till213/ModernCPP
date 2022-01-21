#include <iostream>

class Brush {
public:
    enum struct Color {red, green, blue};
    Color getColor() const;
private:
    Color _color {Color::red};
};

// So far we had to write the implemenation as
//Brush::Color Brush::getColor() const
//{
//    return _color;
//}

// But with post notation we can now write
auto Brush::getColor() const -> Color
{
    return _color;
}

/*!
 * # About
 * The return type of a function can be specified in post notation.
 *
 * # How To Use?
 * Most developers expect the return type in prefix notation. However
 * the post notation becomes very useful in combination with the decltype
 * statement and is used in combination with lambda functions.
 */
int main(int, char *[])
{
    Brush brush;
    std::cout << "The colour is: " << static_cast<std::underlying_type<Brush::Color>::type>(brush.getColor()) << std::endl;

    return 0;
}
