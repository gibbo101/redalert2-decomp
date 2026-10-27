// void HouseClass::Update_Laser_Color() (0x004F5570)
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@4005c000000000000000=007a2f48
// @ref __real@8@4006f000000000000000=007a2f58
// @ref __real@8@4006ff00000000000000=007a2f50
#include "shared/techno.hpp"

void HouseClass::Update_Laser_Color()
{
    double red = unknown_55e9.Red;
    double green = unknown_55e9.Green;
    double blue = unknown_55e9.Blue;
    Normalize_Color(red, green, blue);
    if (red < 96.0) {
        red = 0;
    }
    if (green < 96.0) {
        green = 0;
    }
    if (blue < 96.0) {
        blue = 0;
    }
    Normalize_Color(red, green, blue);
    unknown_55ec.Set(red, green, blue);
}
