// void Tactical::Lepton_To_Map_Pixel(int x, int y, int &pixel_x, int &pixel_y) -- 0x006A6920
// Purpose: projects a map position onto the isometric screen: 60 pixels
// across and 30 down per 256 leptons in X, (-60, 30) in Y, with the X
// result offset by 0x3C00 (TibSun Tactical::Lepton_To_Map_Pixel; the map
// preview 0x0061D5E0/0x0061D660 calls it on the tactical view at 0x0083996C).
// Assumptions: the body does not read this.
#define TACTICAL_DECLARE_LEPTON_TO_MAP_PIXEL
#include "shared/tactical.hpp"

void Tactical::Lepton_To_Map_Pixel(int x, int y, int &pixel_x, int &pixel_y)
{
    pixel_x = (x * 60) / 2;
    pixel_y = (x * 30) / 2;
    pixel_x += (y * -60) / 2;
    pixel_y += (y * 30) / 2;
    pixel_x /= 256;
    pixel_y /= 256;
    pixel_x += 0x3C00;
}
