// void Tactical::Unknown_006AA610(void (__fastcall *callback)(ObjectClass *object)) (0x006AA610): ends the selection band: the
// rectangle spanned by its two corners (+0xD90, +0xD98) goes to 0x006AABC0 with the callback, then the band is cleared.
#include "shared/tactical.hpp"
// @ref ?Unknown_006AABC0@Tactical@@QAEXPBVRect@@P6IXPAVObjectClass@@@Z@Z=006aabc0

void Tactical::Unknown_006AA610(void (__fastcall *callback)(ObjectClass *object))
{
    if (unknown_d90 != Point2D(0, 0)) {
        int left = unknown_d90.X;
        int right = unknown_d98.X;
        int bottom = unknown_d98.Y;
        int top = unknown_d90.Y;
        if (left > right) {
            int swap = left;
            left = right;
            right = swap;
        }
        if (top > bottom) {
            int swap = top;
            top = bottom;
            bottom = swap;
        }
        Rect rect(left, top, right - left + 1, bottom - top + 1);
        Unknown_006AABC0(&rect, callback);
        unknown_d90 = Point2D(0, 0);
    }
}
