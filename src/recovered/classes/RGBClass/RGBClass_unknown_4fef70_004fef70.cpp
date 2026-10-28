// void RGBClass::unknown_4fef70(int ratio, RGBClass const &target) (0x004FEF70)
// Moves each channel toward target's by (ratio & 0xFF)/256, blue first (a
// second out-of-line copy of Adjust, 0x0063CF20, in another order).
#include "shared/rgb_class.hpp"

void RGBClass::unknown_4fef70(int ratio, RGBClass const &target)
{
    int weight = ratio & 0xFF;
    Blue = (unsigned char)(Blue + ((int)target.Blue - (int)Blue) * weight / 256);
    Green = (unsigned char)(Green + ((int)target.Green - (int)Green) * weight / 256);
    Red = (unsigned char)(Red + ((int)target.Red - (int)Red) * weight / 256);
}
