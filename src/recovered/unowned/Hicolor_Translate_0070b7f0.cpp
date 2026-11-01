// void __fastcall Hicolor_Translate(void *buffer, int count) -- 0x0070B7F0
// Converts count 15-bit pixels in place through the pixel table.
#include "shared/unvq_table.hpp"

void __fastcall Hicolor_Translate(void *buffer, int count)
{
    unsigned short *pixel = (unsigned short *)buffer;
    while (count > 0) {
        *pixel = HicolorTable[*pixel];
        pixel++;
        count--;
    }
}
