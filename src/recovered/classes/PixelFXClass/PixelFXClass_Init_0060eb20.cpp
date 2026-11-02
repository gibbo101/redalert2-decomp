// void PixelFXClass::Init(int type) (0x0060EB20)
// @ref ?PixelFXTypes@@3PAUPixelFXTypeStruct@@A=007eb940
// Picks the colours of the given type (Bright darkened by random jitter bits),
// a random screen offset, blend rate and lifetime; restarts the phase.
#include "shared/pixel_fx.hpp"
#include "shared/crt_memory.hpp"

void PixelFXClass::Init(int type)
{
    PixelFXTypeStruct *fx = &PixelFXTypes[type];
    unsigned random = rand();
    XOffset = (random & 0x3F) - 0x1F;
    YOffset = ((random >> 5) & 0x1F) - 0x0F;

    Bright.Red = fx->Bright.Red;
    Bright.Green = fx->Bright.Green;
    Bright.Blue = fx->Bright.Blue;
    if (fx->JitterBits != 0) {
        unsigned mask = (1 << fx->JitterBits) - 1;
        random = rand();
        Bright.Red -= mask & random;
        random >>= fx->JitterBits;
        Bright.Green -= mask & random;
        random >>= fx->JitterBits;
        Bright.Blue -= mask & random;
    }

    Current.Red = Dark.Red = fx->Dark.Red;
    Current.Green = Dark.Green = fx->Dark.Green;
    Current.Blue = Dark.Blue = fx->Dark.Blue;
    Phase = 0;
    unsigned range = fx->MaxRate - fx->MinRate + 1;
    Rate = rand() % range + fx->MinRate;
    Life = rand() & fx->LifeMask;
}
