// bool PixelFXClass::Reduce_Life(int frames) (0x0060ECC0)
// Counts the lifetime down; true (and clamped to 0) once it has run out.
#include "shared/pixel_fx.hpp"

bool PixelFXClass::Reduce_Life(int frames)
{
    Life -= frames;
    if (Life <= 0) {
        Life = 0;
        return true;
    }
    return false;
}
