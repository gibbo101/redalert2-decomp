#include "shared/rgb_class.hpp"
#define MIN(a,b) (((b) < (a)) ? (b) : (a))
#define MAX(a,b) (((b) > (a)) ? (b) : (a))
// @ref __real@4@3fff8000000000000000=0079b7f8
// @ref __real@4@4006ff00000000000000=0079b0a8
// @ref __real@4@00000000000000000000=0079a738
RGBClass::RGBClass(RGBClass const &from, RGBClass const &to, float ratio)
{
    Red = (unsigned char)MAX(MIN(from.Red * (1.0f - ratio) + to.Red * ratio, 255.0f), 0.0f);
    Green = (unsigned char)MAX(MIN(from.Green * (1.0f - ratio) + to.Green * ratio, 255.0f), 0.0f);
    Blue = (unsigned char)MAX(MIN(from.Blue * (1.0f - ratio) + to.Blue * ratio, 255.0f), 0.0f);
}
