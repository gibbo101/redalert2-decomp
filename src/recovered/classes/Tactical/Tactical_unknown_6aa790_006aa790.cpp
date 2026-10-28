// void Tactical::Unknown_006AA790() (0x006AA790): draws the selection band rectangle onto the current
// surface (clipped to the tactical area 0x00839630) in GUI color 15. The width, height and color are
// locals computed before the rectangle (they stay in callee-saved registers).
#include "shared/tactical.hpp"
#include "shared/gadget.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630

extern Rect unknown_rect_839630;

void Tactical::Unknown_006AA790()
{
    if (unknown_d90 != Point2D(0, 0)) {
        int left = unknown_d90.X;
        int right = unknown_d98.X;
        int top = unknown_d90.Y;
        int bottom = unknown_d98.Y;
        if (right < left) {
            int swap = left;
            left = right;
            right = swap;
        }
        if (bottom < top) {
            int swap = top;
            top = bottom;
            bottom = swap;
        }
        int width = right - left + 1;
        int height = bottom - top + 1;
        int color = unknown_drawer_8323c4->Convert(15);
        Rect rect(left, top, width, height);
        unknown_surface_83995c->Draw_Rect(unknown_rect_839630, rect, color);
    }
}
