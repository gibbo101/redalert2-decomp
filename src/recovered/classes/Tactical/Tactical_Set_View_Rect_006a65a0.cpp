// void Tactical::Unknown_006A65A0(Rect const &rect) (0x006A65A0; DisplayClass slot 42)
// Sets the view rectangle (kept in the global at 0x00ABE560, read by the tactical drawing) and re-clamps the
// requested view position through 0x006A8C80, which becomes the view position.
// @ref ?Unknown_006A8C80@Tactical@@QAE_NPAUPoint2D@@@Z=006a8c80
// @ref ?Unknown_006A9170@Tactical@@QAEXXZ=006a9170
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_rect_abe560@@3VRect@@A=00abe560
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"

extern Rect unknown_rect_abe560;

void Tactical::Unknown_006A65A0(Rect const &rect)
{
    unknown_rect_abe560 = rect;
    Point2D clamped = unknown_d74;
    int x;
    int y;
    if (Unknown_006A8C80(&clamped) && !unknown_a40d13) {
        x = clamped.X;
        y = clamped.Y;
    } else {
        x = unknown_d74.X;
        y = unknown_d74.Y;
    }
    unknown_d64 = Point2D(x, y);
    unknown_d74 = Point2D(x, y);
    Unknown_006A9170();
    unknown_d7d = true;
}
