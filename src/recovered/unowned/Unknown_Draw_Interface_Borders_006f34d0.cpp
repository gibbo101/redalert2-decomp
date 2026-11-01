// void Unknown_Draw_Interface_Borders_006F34D0(Surface *surface, Rect const &window) (0x006F34D0)
// On screens 1024 or more wide, blacks out the eight bands around the
// 800x600 interface panel (0x00AC11C0, 0x00AC11C4 and 0x00AC11D0 are the
// panel rectangles 0x006F3E70 lays out).
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_rect_ac11c0@@3PAVRect@@A=00ac11c0
// @ref ?unknown_rect_ac11c4@@3PAVRect@@A=00ac11c4
// @ref ?unknown_rect_ac11d0@@3PAVRect@@A=00ac11d0
#include "shared/rect.hpp"
#include "shared/surface.hpp"

extern int unknown_value_8523e0;                 // screen width
extern Rect *unknown_rect_ac11c0;
extern Rect *unknown_rect_ac11c4;
extern Rect *unknown_rect_ac11d0;

void __fastcall Unknown_Draw_Interface_Borders_006F34D0(Surface *surface, Rect const &window)
{
    if (unknown_value_8523e0 >= 1024) {
        int left = unknown_rect_ac11c0->X;
        int right = unknown_rect_ac11c4->X + unknown_rect_ac11c4->Width;
        int top = unknown_rect_ac11c0->Y;
        int bottom = unknown_rect_ac11d0->Height + unknown_rect_ac11d0->Y;
        Rect rect(0, 0, left, top);
        surface->Fill_Rect(rect, window, 0);
        rect = Rect(left, 0, 800, top);
        surface->Fill_Rect(rect, window, 0);
        rect = Rect(right, 0, left, top);
        surface->Fill_Rect(rect, window, 0);
        rect = Rect(right, top, left, 600);
        surface->Fill_Rect(rect, window, 0);
        rect = Rect(right, bottom, left, 600);
        surface->Fill_Rect(rect, window, 0);
        rect = Rect(left, bottom, 800, top);
        surface->Fill_Rect(rect, window, 0);
        rect = Rect(0, bottom, left, top);
        surface->Fill_Rect(rect, window, 0);
        rect = Rect(0, top, left, 600);
        surface->Fill_Rect(rect, window, 0);
    }
}
