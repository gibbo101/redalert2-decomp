// int Tactical::Unknown_006AA6A0() (0x006AA6A0): 1 when the pixel of a listed
// object (the table at 0x00ABE5F8, +0x7D set) lies inside the selection band
// spanned by +0xD90 and +0xD98, relative to the view position (hypothesis).
#include "shared/tactical.hpp"
#include "shared/object.hpp"
// @ref ?unknown_tactical_pixels_abe5f8@@3PAUTacticalObjectPixel@@A=00abe5f8

int Tactical::Unknown_006AA6A0()
{
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
    if (rect.Is_Valid()) {
        for (int index = 0; index < unknown_db0; index++) {
            TacticalObjectPixel &entry = unknown_tactical_pixels_abe5f8[index];
            if (entry.Object != 0 && entry.Object->unknown_7d) {
                Point2D view = unknown_b0;
                Point2D point(entry.Pixel.X - view.X, entry.Pixel.Y - view.Y);
                if (rect.Is_Point_Within(point)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
