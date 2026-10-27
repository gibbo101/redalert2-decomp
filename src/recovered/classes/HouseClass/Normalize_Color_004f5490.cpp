// void __fastcall Normalize_Color(double &red, double &green, double &blue) (0x004F5490)
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@4006f000000000000000=007a2f58
// @ref __real@8@4006ff00000000000000=007a2f50
#include "shared/techno.hpp"

void __fastcall Normalize_Color(double &red, double &green, double &blue)
{
    double length = unknown_sqrt_4ba410(red * red + green * green + blue * blue);
    if (length == 0.0) {
        blue = 255.0;
        green = 255.0;
        red = 255.0;
    } else {
        red = red * 240.0 / length;
        if (red > 255.0) {
            red = 255.0;
        }
        green = green * 240.0 / length;
        if (green > 255.0) {
            green = 255.0;
        }
        blue = blue * 240.0 / length;
        if (blue > 255.0) {
            blue = 255.0;
        }
    }
}
