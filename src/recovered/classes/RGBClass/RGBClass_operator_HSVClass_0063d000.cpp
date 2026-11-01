// RGBClass::operator HSVClass() const -- 0x0063D000 (TS rgb.cpp)
// The colour as hue (0-255 over six sectors), saturation and value.
#define RGB_DECLARE_TO_HSV
#include "shared/hsv_class.hpp"
#include "shared/rgb_class.hpp"

RGBClass::operator HSVClass() const
{
    int hue;
    int saturation;
    int value;

    int red = Red;
    int green = Green;
    int blue = Blue;

    hue = 0;

    value = (red > green) ? red : green;
    if (blue > value) value = blue;

    int white = (red < green) ? red : green;
    if (blue < white) white = blue;

    saturation = 0;
    if (value) {
        saturation = ((value - white) * 255) / value;
    }

    if (saturation != 0) {
        unsigned int tmp = value - white;
        unsigned int r1 = ((value - red) * 255) / tmp;
        unsigned int g1 = ((value - green) * 255) / tmp;
        unsigned int b1 = ((value - blue) * 255) / tmp;
        if (value == red) {
            if (white == green) {
                tmp = 5 * 256 + b1;
            } else {
                tmp = 1 * 256 - g1;
            }
        } else {
            if (value == green) {
                if (white == blue) {
                    tmp = 1 * 256 + r1;
                } else {
                    tmp = 3 * 256 - b1;
                }
            } else {
                if (white == red) {
                    tmp = 3 * 256 + g1;
                } else {
                    tmp = 5 * 256 - r1;
                }
            }
        }
        hue = tmp / 6;
    }
    HSVClass hsv((unsigned char)hue, (unsigned char)saturation, (unsigned char)value);
    return hsv;
}
