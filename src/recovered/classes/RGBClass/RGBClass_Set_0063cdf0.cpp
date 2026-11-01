// RGBClass &RGBClass::Set(RGBClass const &color, float factor) -- 0x0063CDF0 (TS rgb.cpp)
// This colour as color scaled by factor, each channel clamped to 0..255.
#define RGB_DECLARE_BRIGHTEN
#define RGB_DECLARE_TO_HSV
#include "shared/hsv_class.hpp"
#include "shared/rgb_class.hpp"
#define MIN(a,b) (((b) < (a)) ? (b) : (a))
#define MAX(a,b) (((b) > (a)) ? (b) : (a))
// @ref __real@4@4006ff00000000000000=0079b0a8
// @ref __real@4@00000000000000000000=0079a738

RGBClass &RGBClass::Set(RGBClass const &color, float factor)
{
    Red = (unsigned char)MAX(MIN(color.Red * factor, 255.0f), 0.0f);
    Green = (unsigned char)MAX(MIN(color.Green * factor, 255.0f), 0.0f);
    Blue = (unsigned char)MAX(MIN(color.Blue * factor, 255.0f), 0.0f);
    return *this;
}
