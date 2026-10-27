// void RGBClass::Adjust(int ratio, RGBClass const &target) (0x0063CF20)
// Moves each channel toward target's by (ratio & 0xFF)/256 (Westwood's
// RGBClass::Adjust). Re-plan of the accepted
// RgbTriplet::BlendRgbTowardTarget_0063cf20 (population-32) under its class
// name; the channels are read and written in the original's order.
#include "shared/rgb_class.hpp"

void RGBClass::Adjust(int ratio, RGBClass const &target)
{
    int weight = ratio & 0xFF;
    Red = (unsigned char)(Red + ((int)target.Red - (int)Red) * weight / 256);
    Green = (unsigned char)(Green + ((int)target.Green - (int)Green) * weight / 256);
    Blue = (unsigned char)(Blue + ((int)target.Blue - (int)Blue) * weight / 256);
}
