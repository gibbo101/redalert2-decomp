// void PixelFXClass::Set_Offset(int x, int y) (0x0060ECF0)
// Places the sparkle relative to its owner.
#include "shared/pixel_fx.hpp"

void PixelFXClass::Set_Offset(int x, int y)
{
    XOffset = x;
    YOffset = y;
}
