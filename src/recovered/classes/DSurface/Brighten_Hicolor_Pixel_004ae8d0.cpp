// int Brighten_Hicolor_Pixel(RGBClass const &color, int red, int green, int blue) (0x004AE8D0)
// Adds red/green/blue to color. When one or two channels reach 255 their
// combined excess (halved for a single channel) is added to the channels
// still below 255; every channel is then clamped to 255 and the colour packed
// into a screen pixel. The name is a hypothesis.
#include "shared/hicolor.hpp"
#include "shared/palette.hpp"

int __fastcall Brighten_Hicolor_Pixel(RGBClass const &color, int red_add, int green_add, int blue_add)
{
    int red = color.Red + red_add;
    int green = color.Green + green_add;
    int blue = color.Blue + blue_add;
    int excess = 0;
    int saturated = 0;
    if (red >= 255) {
        saturated++;
        excess += red - 255;
    }
    if (green >= 255) {
        saturated++;
        excess += green - 255;
    }
    if (blue >= 255) {
        saturated++;
        excess += blue - 255;
    }
    if (saturated != 0 && saturated < 3) {
        if (saturated == 1) {
            excess >>= 1;
        }
        if (red < 255) {
            red += excess;
        }
        if (green < 255) {
            green += excess;
        }
        if (blue < 255) {
            blue += excess;
        }
    }
    if (blue > 255) {
        blue = 255;
    }
    if (green > 255) {
        green = 255;
    }
    if (red > 255) {
        red = 255;
    }
    return Build_Hicolor_Pixel(red, green, blue);
}
