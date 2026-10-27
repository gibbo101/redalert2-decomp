// void RadarClass::Unknown_00632700() (0x00632700)
// Builds the 22 dot shapes at +0x1274: shape i is a diamond of cells a by b
// in size, each side its scale (0x007CFC70 / 0x007CFCC8) times the zoom
// +0x1484, rounded, at least 1 for scale 1 and 2 otherwise.
#include "shared/radar.hpp"
extern int unknown_dot_width_7cfc70[22];
extern int unknown_dot_height_7cfcc8[22];
// @ref ?unknown_dot_width_7cfc70@@3PAHA=007cfc70
// @ref ?unknown_dot_height_7cfcc8@@3PAHA=007cfcc8

void RadarClass::Unknown_00632700()
{
    for (int index = 0; index < 22; index++) {
        DynamicVectorClass<Point2D> &dots = unknown_1274[index];
        dots.Clear();
        int scale_a = unknown_dot_width_7cfc70[index];
        int scale_b = unknown_dot_height_7cfcc8[index];
        int a;
        if (scale_a == 1) {
            double size = unknown_1484 + 0.5;
            a = (int)(1.0 > size ? 1.0 : size);
        } else {
            double size = scale_a * unknown_1484 + 0.5;
            a = (int)(2.0 > size ? 2.0 : size);
        }
        int b;
        if (scale_b == 1) {
            double size = unknown_1484 + 0.5;
            b = (int)(1.0 > size ? 1.0 : size);
        } else {
            double size = scale_b * unknown_1484 + 0.5;
            b = (int)(2.0 > size ? 2.0 : size);
        }
        int rows = b + a - 1;
        for (int y = 0; y < rows; y++) {
            int start = (y < b) ? -y : y - b * 2 + 2;
            int end = (y < a) ? y : a * 2 - y - 2;
            for (int x = start; x <= end; x++) {
                dots.Add(Point2D(x, y));
            }
        }
    }
}
