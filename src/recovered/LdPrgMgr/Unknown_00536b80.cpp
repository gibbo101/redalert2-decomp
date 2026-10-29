// Rect __fastcall Unknown_00536b80() -- 0x00536B80
#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
// @ref ?unknown_screen_widths_7add68@@3PAHA=007add68
// @ref ?unknown_screen_heights_7add74@@3PAHA=007add74

Rect __fastcall Unknown_00536b80()
{
    Rect area;
    if (unknown_8523e0 == unknown_screen_widths_7add68[0]) {
        area = Rect(16, 126, 318, 104);
    } else {
        area = Rect(20, 158, 398, 130);
    }
    if (unknown_8523e0 >= unknown_screen_widths_7add68[1]) {
        area.X += (unknown_8523e0 - unknown_screen_widths_7add68[1]) / 2;
        area.Y += (unknown_8523e4 - unknown_screen_heights_7add74[1]) / 2;
    }
    return area;
}
