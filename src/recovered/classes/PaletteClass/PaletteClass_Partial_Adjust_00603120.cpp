// void PaletteClass::Partial_Adjust(int ratio, char *lookup) (0x00603120): the flagged entries toward black.
#include "shared/convert.hpp"
#include "shared/rgb_globals.hpp"
// @ref ?Adjust@RGBClass@@QAEXHABV1@@Z=0063cf20
// @ref ?unknown_rgb_ab6841@@3VRGBClass@@A=00ab6841

void PaletteClass::Partial_Adjust(int ratio, char *lookup)
{
    for (int index = 0; index < 256; index++) {
        if (lookup[index]) {
            Palette[index].Adjust(ratio, unknown_rgb_ab6841);
        }
    }
}
