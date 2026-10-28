// void __fastcall Unknown_006A6800(int x, int y, int *pixel_x, int *pixel_y)
// (0x006A6800): a lepton offset to its screen offset before the division by
// 256. Never called: the Tactical unit expands it inline (0x006A2740 and the
// coordinate-to-pixel family).
#include "shared/tactical.hpp"

void __fastcall Unknown_006A6800(int x, int y, int *pixel_x, int *pixel_y)
{
    *pixel_x = x * 60 / 2;
    *pixel_y = x * 30 / 2;
    *pixel_x += y * -60 / 2;
    *pixel_y += y * 30 / 2;
}
