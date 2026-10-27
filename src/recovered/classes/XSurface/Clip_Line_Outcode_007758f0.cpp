// int Clip_Line_Outcode(Rect const &rect, double x, double y) (0x007758F0)
// Cohen-Sutherland region code of a point against rect: 1 left, 2 right
// (at or beyond the excluded right edge), 8 above, 4 at or below the
// excluded bottom edge. Clip_Line (0x00775620) expands it inline. The name is
// a hypothesis.
#include "shared/rect.hpp"

int __fastcall Clip_Line_Outcode(Rect const &rect, double x, double y)
{
    int code = 0;
    if (x >= rect.X + rect.Width) {
        code = 2;
    } else if (x < rect.X) {
        code = 1;
    }
    if (y >= rect.Y + rect.Height) {
        code |= 4;
    } else if (y < rect.Y) {
        code |= 8;
    }
    return code;
}
