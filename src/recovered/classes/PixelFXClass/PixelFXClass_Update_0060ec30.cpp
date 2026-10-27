// void PixelFXClass::Update(int frames) (0x0060EC30)
// Advances the phase and blends the current colour: Dark at phase 0 and
// 0x2000, Bright at 0x1000 (12-bit fixed point). The phase stops at 0x2000.
#include "shared/pixel_fx.hpp"

void PixelFXClass::Update(int frames)
{
    Phase += Rate * frames;
    if (Phase > 0x2000) {
        Phase = 0x2000;
    }

    int blend = Phase & 0xFFF;
    if (Phase & 0x1000) {
        blend = 0x1000 - blend;
    }

    Current.Red = (Dark.Red * (0x1000 - blend) + Bright.Red * blend) >> 12;
    Current.Green = (Dark.Green * (0x1000 - blend) + Bright.Green * blend) >> 12;
    Current.Blue = (Dark.Blue * (0x1000 - blend) + Bright.Blue * blend) >> 12;
}
