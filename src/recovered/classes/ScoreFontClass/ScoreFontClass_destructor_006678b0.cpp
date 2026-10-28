// ScoreFontClass::~ScoreFontClass() (0x006678B0)
// Frees an owned sheet; the last font forgets the typing sounds.
#include "shared/score_font.hpp"
// @ref ??_7ScoreFontClass@@6B@=007a92a0
// @ref ?unknown_score_fonts_ab6fa4@@3HA=00ab6fa4
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_score_sounds_ab6fa8@@3PAUScoreFontSound@@A=00ab6fa8

ScoreFontClass::~ScoreFontClass()
{
    if (Image && IsAllocated == true) {
        delete (void *)Image;
        Image = 0;
        IsAllocated = false;
    }
    if (--unknown_score_fonts_ab6fa4 == 0) {
        for (int i = 0; i < 3; i++) {
            unknown_score_sounds_ab6fa8[i].Data = 0;
            unknown_score_sounds_ab6fa8[i].IsAllocated = false;
        }
    }
}
