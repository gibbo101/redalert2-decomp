// PaletteClass::PaletteClass(RGBClass const &rgb) (0x00602FD0): every entry set to rgb.
// Unit-wide (Westwood palette.cpp, 0x00602FD0-0x006031F4): convert.hpp's guarded palette.cpp members.
#define PALETTE_DECLARE_MEMBERS
#include "shared/convert.hpp"

PaletteClass::PaletteClass(RGBClass const &rgb)
{
    for (int index = 0; index < 256; index++) {
        Palette[index] = rgb;
    }
}
