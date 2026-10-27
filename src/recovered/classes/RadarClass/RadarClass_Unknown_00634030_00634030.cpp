// void RadarClass::Unknown_00634030() (0x00634030)
// Redraws the whole radar: with no window, copies the surface at +0x121C
// onto the one at +0x1218 and finishes with 0x006324A0; otherwise draws
// every point of the radar surface.
#include "shared/radar.hpp"
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Unknown_006324A0@RadarClass@@QAEXXZ=006324a0
// @ref ?Unknown_00632000@RadarClass@@QAEXABUPoint2D@@@Z=00632000

void RadarClass::Unknown_00634030()
{
    if (!MainWindow) {
        unknown_1218->Copy_From(unknown_1218->Get_Rect(), *unknown_121c, unknown_121c->Get_Rect(), false, true);
        Unknown_006324A0();
    } else {
        int width = unknown_1218->Get_Width();
        int height = unknown_1218->Get_Height();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Unknown_00632000(Point2D(x, y));
            }
        }
    }
}
