// void RadarClass::Unknown_00631E40() (0x00631E40)
// Releases the radar's two surfaces, its buffers and its tracking table.
#include "shared/radar.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void RadarClass::Unknown_00631E40()
{
    if (unknown_1218) {
        delete unknown_1218;
        unknown_1218 = 0;
    }
    if (unknown_121c) {
        delete unknown_121c;
        unknown_121c = 0;
    }
    if (unknown_1238.unknown_00) {
        delete[] unknown_1238.unknown_00;
        unknown_1238.unknown_00 = 0;
    }
    if (unknown_1254) {
        delete unknown_1254;
        unknown_1254 = 0;
    }
    if (unknown_1270) {
        delete[] unknown_1270;
        unknown_1270 = 0;
    }
}
