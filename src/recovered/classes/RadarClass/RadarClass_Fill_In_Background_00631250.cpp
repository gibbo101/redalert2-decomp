// void RadarClass::Unknown_00631250(Rect const &cell_rect, Rect const &update_rect) (0x00631250)
// TibSun's Fill_In_Background: for every map cell inside the update area of
// the radar cell grid, stores its two radar colours (CellClass 0x004712C0)
// into the background colour buffer (+0x1238), one at the left/right edges.
#include "shared/radar.hpp"
#include "shared/map_cell.hpp"
#include "shared/rgb_class.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_004712c0@CellClass@@QAEXPAVRGBClass@@0@Z=004712c0

void RadarClass::Unknown_00631250(Rect const &cell_rect, Rect const &update_rect)
{
    RGBClass low(0, 0, 0);
    RGBClass high(0, 0, 0);
    Unknown_0055A550();
    CellClass *iter = Map.Unknown_0055A490();
    int a = 2 * Map.MapLocalSize.X - Map.MapSize.Width + 1;
    while (iter != 0) {
        int x = iter->MapCoords.X;
        int y = iter->MapCoords.Y;
        if (x + y >= unknown_1494) {
            int origx = x - y - a;
            int origy = x + y - unknown_1494;
            Rect mrect(origx, origy, 2, 1);
            mrect = Intersect(mrect, update_rect);
            if (mrect.Is_Valid()) {
                int idx = mrect.X + mrect.Y * cell_rect.Width;
                iter->Unknown_004712c0(&low, &high);
                if (origx == update_rect.X - 1) {
                    BackgroundColors[idx] = high;
                } else if (origx == update_rect.Width + update_rect.X - 1) {
                    BackgroundColors[idx] = low;
                } else {
                    BackgroundColors[idx] = low;
                    BackgroundColors[idx + 1] = high;
                }
            }
        }
        iter = Map.Unknown_0055A490();
    }
}
