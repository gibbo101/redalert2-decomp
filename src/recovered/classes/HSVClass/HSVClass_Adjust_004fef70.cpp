// void HSVClass::Adjust(int ratio, HSVClass const &hsv) (0x004FEF70)
// Moves the colour toward hsv by (ratio & 0xFF)/256: value, saturation, then hue (Tiberian Sun's
// hsv.cpp Adjust). Declared only in the HSV unit (RA2_HSV_UNIT, shared/hsv_class.hpp).
#define RA2_HSV_UNIT
#include "shared/hsv_class.hpp"

void HSVClass::Adjust(int ratio, HSVClass const &hsv)
{
    ratio &= 0x00FF;

    int value = hsv.Value - Value;
    Value = (unsigned char)(Value + (value * ratio) / 256);

    int saturation = hsv.Saturation - Saturation;
    Saturation = (unsigned char)(Saturation + (saturation * ratio) / 256);

    int hue = hsv.Hue - Hue;
    Hue = (unsigned char)(Hue + (hue * ratio) / 256);
}
