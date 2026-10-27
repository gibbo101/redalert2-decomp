// int DSurface::Bytes_Per_Pixel() (0x004AAC60, slot 28)
// Pixel size from the surface's pixel format.
#include "shared/dsurface.hpp"

int DSurface::Bytes_Per_Pixel()
{
    return BytesPerPixel;
}
