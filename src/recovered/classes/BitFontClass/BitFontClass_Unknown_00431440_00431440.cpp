// unsigned short BitFontClass::Unknown_00431440(unsigned short value) (0x00431440)
// Stores value in the word after the text colour (+0x26) and returns the colour (+0x24). Unreferenced and
// without an inventory row (between Set_Color 0x00431430 and Set_Clipping 0x00431450).
#include "shared/text_print.hpp"

unsigned short BitFontClass::Unknown_00431440(unsigned short value)
{
    unknown_26 = value;
    return Color;
}
