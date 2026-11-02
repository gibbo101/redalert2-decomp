// AlphaLightingRemapClass::AlphaLightingRemapClass(int level) (0x0041E590)
#include "shared/alpha_lighting_remap.hpp"

AlphaLightingRemapClass::AlphaLightingRemapClass(int level)
    : Level(level), RefCount(0)
{
    for (int index = 0; index <= 0xFFFF; index++) {
        int value = (index & 0xFF) * (index >> 8) * (level - 1) / 0x7E02;
        if (value > level - 1) {
            value = level - 1;
        }
        Table[index] = (unsigned short)((unsigned char)value << 8);
    }
}
