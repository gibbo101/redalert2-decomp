// void RadarClass::Unknown_00631600() (0x00631600)
// TibSun's Plot_Radar_Background: recolours the background (+0x1238) of every
// cell waiting at +0x1220 that is inside the local radar, rebuilds the radar
// image over the area it changed (0x00630B70) and keeps the union of those
// areas at +0x1244 (TibSun CellRedrawRect).
#include "shared/radar.hpp"
#include "shared/map_cell.hpp"
#include "shared/rgb_class.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_004712c0@CellClass@@QAEXPAVRGBClass@@0@Z=004712c0

void RadarClass::Unknown_00631600()
{
    Rect r(0, 0, 0, 0);
    for (int i = unknown_1220.Count() - 1; i >= 0; i--) {
        Cell cell = unknown_1220[i];
        if (Unknown_0055A660(cell, true)) {
            Rect update_rect = Unknown_00631400(cell);
            int x = update_rect.X;
            Rect cellgrid(0, 0, RadarCellWidth, RadarCellHeight);
            update_rect = Intersect(update_rect, cellgrid);
            if (update_rect.Is_Valid()) {
                RGBClass low(0, 0, 0);
                RGBClass high(0, 0, 0);
                CellClass *cptr = &Map[cell];
                int idx = update_rect.X + update_rect.Y * RadarCellWidth;
                cptr->Unknown_004712c0(&low, &high);
                if (x == 0 && update_rect.Width == 1) {
                    BackgroundColors[idx + 1] = high;
                } else if (update_rect.Width == 1) {
                    BackgroundColors[idx] = low;
                } else {
                    BackgroundColors[idx] = low;
                    BackgroundColors[idx + 1] = high;
                }
                Rect radarcellrect(0, 0, RadarCellWidth, RadarCellHeight);
                Rect rr = Unknown_00630B70(radarcellrect, update_rect, false);
                r = Union(r, rr);
            }
        }
    }
    unknown_1220.Clear();
    unknown_1244 = r;
}
