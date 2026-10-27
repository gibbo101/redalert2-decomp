// void __fastcall TabClass::Unknown_006A0670(int rows) (0x006A0670)
// Sets the bar's row count and its edge: the 0x00AC1210 rectangle's X less
// rows widths of the 0x00AC120C rectangle, but not less than the right edge
// of the 0x00AC1204 rectangle.
#include "shared/tab.hpp"
// @ref ?unknown_int_abe2ac@@3HA=00abe2ac
// @ref ?unknown_int_abe37c@@3HA=00abe37c
// @ref ?unknown_rect_ac1204@@3PBVRect@@B=00ac1204
// @ref ?unknown_rect_ac120c@@3PBVRect@@B=00ac120c
// @ref ?unknown_rect_ac1210@@3PBVRect@@B=00ac1210

void __fastcall TabClass::Unknown_006A0670(int rows)
{
    unknown_int_abe2ac = rows;
    int top = unknown_rect_ac1210->X - rows * unknown_rect_ac120c->Width;
    int limit = unknown_rect_ac1204->X + unknown_rect_ac1204->Width;
    unknown_int_abe37c = top > limit ? top : limit;
}
