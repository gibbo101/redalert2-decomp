// ScoreFontClass::ScoreFontClass() (0x00667840)
// The unit's shape helpers fall back on Score.cpp's empty rectangle.
#define SHAPE_FILE_EMPTY_RECT unknown_score_empty_rect_ab6f20
#include "shared/score_font.hpp"
// @ref ??_7ScoreFontClass@@6B@=007a92a0
// @ref ?unknown_score_fonts_ab6fa4@@3HA=00ab6fa4
// @ref ?Load_Sounds@ScoreFontClass@@QAEXXZ=00667900

ScoreFontClass::ScoreFontClass() :
    Width(0),
    Height(0),
    Image(0),
    Drawer(0)
{
    Load_Sounds();
    unknown_score_fonts_ab6fa4++;
}
