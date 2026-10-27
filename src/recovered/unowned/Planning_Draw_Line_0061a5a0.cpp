#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Line(int offset, int color, Point2D start, Point2D end, bool dashed) (0x0061A5A0)
// Draws a line between two screen points, shifted sideways by offset pixels
// (in y for a mostly horizontal line, else in x) and clipped to the tactical
// area; dashed lines crawl with the clock.
#include "shared/planning.hpp"
#include "shared/surface.hpp"
#include "shared/rect.hpp"
// @ref ?unknown_int_839638@@3HA=00839638
// @ref ?unknown_int_83963c@@3HA=0083963c
// @ref ?unknown_pattern_7eb9f8@@3PA_NA=007eb9f8
// @ref ?Clip_Line@@YI_NAAUPoint2D@@0ABVRect@@@Z=00775620

extern int unknown_int_839638;
extern int unknown_int_83963c;
extern bool unknown_pattern_7eb9f8[16];

void __fastcall Planning_Draw_Line(int offset, int color, Point2D start, Point2D end, bool dashed)
{
    bool steep = abs(end.X - start.X) > abs(end.Y - start.Y);
    int sideways = steep ? 0 : offset;
    int lengthways = steep ? offset : 0;
    start.X += sideways;
    start.Y += lengthways;
    end.X += sideways;
    end.Y += lengthways;
    Rect area(unknown_int_839630, unknown_int_839634, unknown_int_839638, unknown_int_83963c);
    if (Clip_Line(start, end, area)) {
        if (dashed) {
            int phase = (-(int)timeGetTime() >> 5) & 0xF;
            unknown_surface_839964->Draw_Dashed_Line(start, end, color, unknown_pattern_7eb9f8, phase);
        } else {
            unknown_surface_839964->Draw_Line(start, end, color);
        }
    }
}
