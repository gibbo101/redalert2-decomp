#define SHAPE_FILE_EMPTY_RECT unknown_score_empty_rect_ab6f20
#include "shared/score_font.hpp"
#include "shared/shape_file.hpp"
#include "shared/msfont.hpp"
// @ref ?unknown_score_empty_rect_ab6f20@@3VRect@@B=00ab6f20

int ScoreFontClass::Char_Pixel_Width(unsigned short character)
{
    char c = (char)character;
    if (character == ' ') {
        return 8;
    }
    char ch;
    CharToOemBuffA(&c, &ch, 1);
    // The unsigned lower choice preserves negative signed-byte offsets.
    int index = ((ch - '!') > 0U ? (ch - '!') : 0U);
    if (index >= 0xD8) {
        index = 0xD8;
    }
    return Image->Get_Frame_Rect(index * 3 + 2).Width;
}
