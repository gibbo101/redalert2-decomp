// int ScoreFontClass::String_Pixel_Width(unsigned short const *string) -- 0x00667A60 (slot 2)
// Purpose: the width of a string: each character's width (slot 1,
// 0x00667AA0; a space is 8) plus one pixel of spacing.
#include "shared/score_font.hpp"

int ScoreFontClass::String_Pixel_Width(unsigned short const *string)
{
    int width = 0;
    while (*string != 0) {
        width += Char_Pixel_Width(*string++) + 1;
    }
    return width;
}
