// void __fastcall Rebuild_Interpolated_Palette(unsigned char *interpal) (0x005A0250)
// Mirrors the stored triangle of the 256 x 256 interpolation table across its diagonal.
#include "shared/play_movie.hpp"

void __fastcall Rebuild_Interpolated_Palette(unsigned char *interpal)
{
    for (int y = 0; y < 256 - 1; y++) {
        for (int x = y + 1; x < 256; x++) {
            *(interpal + (y * 256 + x)) = *(interpal + (x * 256 + y));
        }
    }
}
