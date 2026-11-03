// void WaveClass::Set_Laser_Pixel_00721b00(unsigned short *pixel, int mult) const (0x00721B00)
// Brightens one screen pixel under a laser wave (TibSun Set_Laser_Pixel): red and
// blue are raised by the wave's strength, every channel is clamped to 255. No
// caller in the executable; Draw_Laser 0x00722CB0 expands it inline.
#include "shared/wave.hpp"
#include "shared/hicolor.hpp"

// Westwood's always.h MIN.
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

void WaveClass::Set_Laser_Pixel_00721b00(unsigned short *pixel, int mult) const
{
    RGBClass rgb = Deconstruct_Hicolor_Pixel(*pixel);
    int red = rgb.Red;
    int green = rgb.Green;
    int blue = rgb.Blue;
    red += ((mult * 64) >> 8);
    blue += ((mult * 3 * 32) >> 8);
    *pixel = Build_Hicolor_Pixel(MIN(255, red), MIN(255, green), MIN(255, blue));
}
