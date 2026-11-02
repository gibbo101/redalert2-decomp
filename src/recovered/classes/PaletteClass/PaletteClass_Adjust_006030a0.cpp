// void PaletteClass::Adjust(int ratio) (0x006030A0): every entry toward black by ratio/256.
#include "shared/convert.hpp"
#include "shared/rgb_globals.hpp"
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20
// @ref ?unknown_rgb_ab6841@@3VRGBClass@@A=00ab6841

void PaletteClass::Adjust(int ratio)
{
    for (int index = 0; index < 256; index++) {
        Palette[index].Adjust(ratio, unknown_rgb_ab6841);
    }
}
