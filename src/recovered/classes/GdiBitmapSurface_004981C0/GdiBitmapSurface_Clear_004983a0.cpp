// Fill only logical Width*Height bytes, preserving the original tight-size count.
#include "shared/gdi_bitmap_surface.hpp"
#include "shared/crt_memory.hpp"
void GdiBitmapSurface_004981C0::Clear(unsigned char color)
{
    if (Bits) memset(Bits, color, (unsigned int)Height * (unsigned int)Width);
}
