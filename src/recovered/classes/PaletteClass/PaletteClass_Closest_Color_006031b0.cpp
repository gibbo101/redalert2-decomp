// int PaletteClass::Closest_Color(RGBClass const &rgb) const (0x006031B0): the entry with the smallest
// RGBClass::Difference (Westwood palette.cpp).
#include "shared/convert.hpp"
// @ref ?Difference@RGBClass@@QBEHABV1@@Z=0063cfb0

int PaletteClass::Closest_Color(RGBClass const &rgb) const
{
    int closest = 0;
    int value = -1;

    RGBClass const *ptr = &Palette[0];
    for (int index = 0; index < 256; index++) {
        int difference = rgb.Difference(*ptr++);
        if (value == -1 || difference < value) {
            value = difference;
            closest = index;
        }
    }
    return closest;
}
