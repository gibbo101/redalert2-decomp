// int __fastcall Buffer_Size(Surface &surface, int width, int height) (0x00434940)
// Bytes needed for a width x height block of the surface's pixels.
#include "shared/blit.hpp"

int __fastcall Buffer_Size(Surface &surface, int width, int height)
{
    return surface.Bytes_Per_Pixel() * width * height;
}
