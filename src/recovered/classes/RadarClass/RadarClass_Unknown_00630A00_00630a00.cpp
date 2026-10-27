// void RadarClass::Unknown_00630A00() (0x00630A00)
// Rebuilds the radar surfaces for a non-empty radar rectangle: drops the old
// image, buffers and drawing surface, renders the image (0x00630B70),
// centres the rectangle in the 140 x 108 radar area, and makes a cleared
// drawing surface of the image's size before 0x00632700.
#include "shared/radar.hpp"
#include "shared/dsurface.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Unknown_00630B70@RadarClass@@QAE?AVRect@@ABV2@0_N@Z=00630b70
// @ref ??0DSurface@@QAE@HH_N@Z=004aa4a0
// @ref ?Unknown_00632700@RadarClass@@QAEXXZ=00632700

void RadarClass::Unknown_00630A00()
{
    if (unknown_1498.Is_Valid()) {
        unknown_1498.Y = 0;
        unknown_1498.X = 0;
        if (unknown_121c) {
            delete unknown_121c;
            unknown_121c = 0;
        }
        if (unknown_1238.unknown_00) {
            delete[] unknown_1238.unknown_00;
            unknown_1238.unknown_00 = 0;
        }
        if (unknown_1270) {
            delete[] unknown_1270;
            unknown_1270 = 0;
        }
        Unknown_00630B70(unknown_1498, unknown_1498, true);
        unknown_1498.Width = unknown_121c->Get_Width();
        unknown_1498.Height = unknown_121c->Get_Height();
        unknown_1498.X = unknown_11ec;
        if (unknown_1498.Width < 140) {
            unknown_1498.X = (140 - unknown_1498.Width) / 2 + unknown_11ec;
        }
        unknown_1498.Y = unknown_11f0;
        if (unknown_1498.Height < 108) {
            unknown_1498.Y = (108 - unknown_1498.Height) / 2 + unknown_11f0;
        }
        if (unknown_1218) {
            delete unknown_1218;
            unknown_1218 = 0;
        }
        unknown_1218 = new DSurface(unknown_121c->Get_Width(), unknown_121c->Get_Height(), true);
        unknown_1218->Fill(0);
        Unknown_00632700();
    }
}
