// void Tactical::Unknown_006A6640(Point2D const &point) (0x006A6640)
// Sets the view position to a point clamped by 0x006A8C80 (the point itself while the clamp refuses or the
// flag at 0x00A40D13 is set) and flags the view for a redraw.
// @ref ?Unknown_006A8C80@Tactical@@QAE_NPAUPoint2D@@@Z=006a8c80
// @ref ?Unknown_006A9170@Tactical@@QAEXXZ=006a9170
// @ref ?unknown_a40d13@@3_NA=00a40d13
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"

void Tactical::Unknown_006A6640(Point2D const &point)
{
    Point2D clamped = point;
    int x;
    int y;
    if (Unknown_006A8C80(&clamped) && !unknown_a40d13) {
        x = clamped.X;
        y = clamped.Y;
    } else {
        x = point.X;
        y = point.Y;
    }
    unknown_d64 = Point2D(x, y);
    unknown_d74 = Point2D(x, y);
    Unknown_006A9170();
    unknown_d7d = true;
}
