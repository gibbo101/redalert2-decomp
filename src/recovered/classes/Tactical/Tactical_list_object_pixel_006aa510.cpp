// bool Tactical::Unknown_006AA510(ObjectClass *object, int x, int y) (0x006AA510): lists an
// object with its pixel (x, y plus the view position) in the table at 0x00ABE5F8
// when the table has room and the point is within 32 pixels of the tactical area
// (hypothesis; 0x006AA300 expands it).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_tactical_pixels_abe5f8@@3PAUTacticalObjectPixel@@A=00abe5f8

bool Tactical::Unknown_006AA510(ObjectClass *object, int x, int y)
{
    if (unknown_db0 != 500 && x >= -32 && x <= unknown_rect_839630.Width + 32 && y >= -32 && y <= unknown_rect_839630.Height + 32) {
        unknown_tactical_pixels_abe5f8[unknown_db0].Object = object;
        Point2D view = unknown_b0;
        unknown_tactical_pixels_abe5f8[unknown_db0].Pixel = Point2D(x + view.X, y + view.Y);
        unknown_db0++;
        return true;
    }
    return false;
}
