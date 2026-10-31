// void WaveClass::Brighten_Pixel_007219c0(int x, int offset, int row, unsigned short *pixel) (0x007219C0)
// Sonic wave distortion of one screen pixel (TibSun Set_Sonic_Pixel): the
// ripple amplitude at the pixel's radius picks a neighbour sample along the
// wave's direction, whose green and blue are raised by the intensity table.
#include "shared/wave.hpp"
#include "shared/hicolor.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Wave_Distance_Table_00af9620@@3PAY0BCM@GA=00af9620
// @ref ?Wave_Sine_Table_00af91e4@@3PAFA=00af91e4
// @ref ?Wave_Intensity_Table_00af95d8@@3PAHA=00af95d8

// Red Alert's JSHELL.H min (a template, unlike the MIN macro; the green
// clamp needs its by-value temporary).
template <class T> inline T min(T a, T b) { return (a < b) ? a : b; }
void WaveClass::Brighten_Pixel_007219c0(int x, int offset, int row, unsigned short *pixel)
{
    int radius = Wave_Distance_Table_00af9620[row][abs(x - unknown_b8.X - offset)];
    int amplitude = abs(Wave_Sine_Table_00af91e4[unknown_11c + radius]);
    unsigned short color = pixel[PixelOffsets_1d0[amplitude]];
    int mult = Wave_Intensity_Table_00af95d8[amplitude];

    RGBClass rgb = Unpack_Hicolor_Pixel(color);
    int red = rgb.Red;
    int green = rgb.Green;
    int blue = rgb.Blue;
    green += ((green * mult) >> 8);
    blue += ((blue * mult) >> 8);

    *pixel = Build_Hicolor_Pixel(red, min(255, green), min(255, blue));
}
