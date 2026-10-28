// AlphaLightingRemapClass::AlphaLightingRemapClass(int level) (0x0041E590)
#include "shared/alpha_lighting_remap.hpp"

AlphaLightingRemapClass::AlphaLightingRemapClass(int level)
    : Level(level), RefCount(0)
{
    int top = level - 1;
    for (int index = 0; index <= 0xFFFF; index++) {
        int value = (index & 0xFF) * (index >> 8) * top / 0x7E02;
        if (value > top) {
            value = top;
        }
        Table[index] = (unsigned short)((unsigned char)value << 8);
    }
}
