// void MapClass::Unknown_005499C0() (0x005499C0)
// Rebuilds the zone data for the map size: frees and reallocates the +0x64
// elements ((width + height + 1) squared, +0x68) and the +0x6C buffer (ten
// bytes per element), sizes the path estimator for the map rectangle, sets
// the three subzone tracking vectors' growth steps (width * height * 4 over
// 4, 16 and 64), runs 0x0054B2E0, 0x0054FDA0 and 0x0054EBD0 and rebuilds the
// subzone tracking (0x00563D40).
#include "shared/map.hpp"
#include "shared/path_estimator.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_path_estimator_8315c8@@3UUnknownPathEstimator@@A=008315c8
// @ref ?Unknown_004284E0@UnknownPathEstimator@@QAEXABVRect@@@Z=004284e0
// @ref ?Unknown_0054B2E0@MapClass@@QAEXXZ=0054b2e0
// @ref ?Unknown_0054FDA0@MapClass@@QAEXXZ=0054fda0
// @ref ?Unknown_0054EBD0@MapClass@@QAEXXZ=0054ebd0

void MapClass::Unknown_005499C0()
{
    if (unknown_64 != 0) {
        delete unknown_64;
        unknown_64 = 0;
    }
    if (unknown_6c != 0) {
        delete unknown_6c;
        unknown_6c = 0;
    }
    int size = MapSize.Width + MapSize.Height + 1;
    unknown_68 = size * size;
    unknown_64 = new UnknownMapElem4[unknown_68];
    unknown_6c = new char[unknown_68 * 10];
    unknown_path_estimator_8315c8.Unknown_004284E0(MapSize);
    for (int index = 0; index < 3; index++) {
        int scale = 1 << (index + 1);
        SubzoneTracking[index].Set_Growth_Step(MapSize.Width * MapSize.Height * 4 / (scale * scale));
    }
    Unknown_0054B2E0();
    Unknown_0054FDA0();
    Unknown_0054EBD0();
    Unknown_00563D40();
}
