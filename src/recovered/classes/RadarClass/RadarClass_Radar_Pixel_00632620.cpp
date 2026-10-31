// void RadarClass::Unknown_00632620(Point2D const &point) (0x00632620)
// TibSun's Radar_Pixel: marks a radar pixel inside the radar surface (+0x1218)
// once in the pixel bit flags (+0x1270), queues it (+0x1258) and notes pending
// work (+0x14D5).
#include "shared/radar.hpp"

void RadarClass::Unknown_00632620(Point2D const &point)
{
    if (point.X >= 0 && point.X < unknown_1218->Get_Width() && point.Y >= 0 && point.Y < unknown_1218->Get_Height()) {
        int id = point.X + point.Y * unknown_1218->Get_Width();
        int i = id >> 3;
        int bit = 1 << (id & 7);
        if ((unknown_1270[i] & bit) == 0) {
            unknown_1270[i] |= bit;
            unknown_1258.Add(point);
            unknown_14d5 = true;
        }
    }
}
