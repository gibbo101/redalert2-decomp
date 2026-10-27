// void DisplayClass::unknown_slot47(Point2D const &xy) (0x0049C500, slot 47)
// The left mouse button held at xy (hypothesis: Westwood's Mouse_Left_Held):
// a band being dragged follows the point, clamped to the tactical area; a
// press that has moved more than 4 pixels from where it started begins the
// band. Neither happens in the waypoint mode (+0x11AF) or the mode +0x11B0.
#include "shared/display.hpp"
#include "shared/tactical.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006AA5A0@Tactical@@QAEXABUPoint2D@@@Z=006aa5a0
// @ref ?Unknown_006AA5E0@Tactical@@QAEXABUPoint2D@@@Z=006aa5e0
// @ref ?Override_Mouse_Shape@MouseClass@@UAE_NH_N@Z=0059f250
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410

void DisplayClass::unknown_slot47(Point2D const &xy)
{
    if (unknown_11cb && !unknown_11af && !unknown_11b0) {
        Rect area = unknown_rect_839630;
        int x = xy.X;
        int y = xy.Y;
        if (x < 0) {
            x = 0;
        }
        if (x >= area.Width) {
            x = area.Width - 1;
        }
        if (y < 0) {
            y = 0;
        }
        if (y >= area.Height) {
            y = area.Height - 1;
        }
        Point2D point(x, y);
        if (point != unknown_11d8) {
            unknown_tactical_83996c->unknown_d7d = true;
            unknown_tactical_83996c->Unknown_006AA5E0(point);
        }
    } else if (unknown_11cc) {
        Point2D const &start = unknown_11d0;
        Point2D delta(xy.X - start.X, xy.Y - start.Y);
        if ((int)unknown_sqrt_4ba410((double)delta.X * delta.X + (double)delta.Y * delta.Y) > 4) {
            unknown_11cb = true;
            unknown_11cc = false;
            if (!unknown_11af && !unknown_11b0) {
                unknown_tactical_83996c->unknown_d7d = true;
                unknown_tactical_83996c->Unknown_006AA5A0(start);
                Map.Override_Mouse_Shape(0, false);
            }
        }
    }
}
