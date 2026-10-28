// void __fastcall Unknown_Quantize_Color_005385a0(int *red, int *green, int *blue) (0x005385A0)
// Clamps three colour components to 0..1000 and drops their low bits by the detail level
// (0x00A40B2C: 0 keeps multiples of 128, 1 of 64, 2 of 32, anything else keeps them).
#include "shared/unknown_globals.hpp"
// @ref ?unknown_a40b2c@@3HA=00a40b2c

void __fastcall Unknown_Quantize_Color_005385a0(int *red, int *green, int *blue)
{
    int value = *red;
    if (value >= 1000) {
        value = 1000;
    }
    *red = value;
    value = *green;
    if (value >= 1000) {
        value = 1000;
    }
    *green = value;
    value = *blue;
    if (value >= 1000) {
        value = 1000;
    }
    *blue = value;
    *red = (*red <= 0 ? 0 : *red);
    *green = (*green <= 0 ? 0 : *green);
    *blue = (*blue <= 0 ? 0 : *blue);
    switch (unknown_a40b2c) {
    case 0:
        *red &= ~127;
        *green &= ~127;
        *blue &= ~127;
        break;
    case 1:
        *red &= ~63;
        *green &= ~63;
        *blue &= ~63;
        break;
    case 2:
        *red &= ~31;
        *green &= ~31;
        *blue &= ~31;
        break;
    }
}
