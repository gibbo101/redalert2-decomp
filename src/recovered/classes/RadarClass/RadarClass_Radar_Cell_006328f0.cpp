// void RadarClass::Unknown_006328F0(Cell const &cell) (0x006328F0)
// TibSun's Radar_Cell: the cell's diamond rectangle (0x00631400, expanded),
// clipped to the radar cell size (+0x1238), scaled by the zoom (+0x1484) with
// a one-pixel margin, every pixel marked through 0x00632620.
#include "shared/radar.hpp"
// @ref __ftol=0077f110

void RadarClass::Unknown_006328F0(Cell const &cell)
{
    if (unknown_1218 != 0) {
        Rect r1 = Unknown_00631400(cell);
        r1 = Intersect(r1, Rect(0, 0, unknown_1238.unknown_04, unknown_1238.unknown_08));
        int swidth = unknown_1218->Get_Width();
        int sheight = unknown_1218->Get_Height();
        if (r1.Is_Valid()) {
            int zx = (int)(r1.X * unknown_1484);
            int startx = (zx - 1 < 0) ? 0 : zx - 1;
            int ex = (int)((double)(r1.X + r1.Width) * unknown_1484) + 1;
            int width = (ex < swidth) ? ex : swidth;
            int zy = (int)(r1.Y * unknown_1484);
            int starty = (zy - 1 < 0) ? 0 : zy - 1;
            int ey = (int)((double)(r1.Y + r1.Height) * unknown_1484) + 1;
            int height = (ey < sheight) ? ey : sheight;
            for (int y = starty; y < height; y++) {
                for (int x = startx; x < width; x++) {
                    Unknown_00632620(Point2D(x, y));
                }
            }
        }
    }
}
