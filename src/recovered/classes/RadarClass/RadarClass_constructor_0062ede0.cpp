// RadarClass::RadarClass() (0x0062EDE0)
// Clears the radar's state, builds its vectors and its 256-bucket tracking
// table (hash 0x00631C60, growth 10), and sets the point list's growth step
// to 500.
#include "shared/radar.hpp"
// @ref ??0DisplayClass@@QAE@XZ=00498a50
// @ref ?unknown_rect_ab6320@RadarClass@@2VRect@@A=00ab6320
// @ref ?Unknown_00631C60@@YIHABURadarTrackingStruct@@@Z=00631c60
// @ref ?Unknown_00405BF0@UnknownList14BC@@QAEXXZ=00405bf0
// @ref ??2@YAPAXI@Z=00782017

static inline HashTableClass<RadarTrackingStruct, TechnoClass *> *Make_Table(int count, int growth)
{
    return new HashTableClass<RadarTrackingStruct, TechnoClass *>(growth, count, Unknown_00631C60);
}

RadarClass::RadarClass()
    : unknown_11e4(0), unknown_11e8(0), unknown_11ec(0), unknown_11f0(0), unknown_11f4(0), unknown_11f8(0),
      unknown_11fc(0), unknown_1200(0), unknown_1208(unknown_rect_ab6320), unknown_1218(0), unknown_121c(0),
      unknown_1244(0, 0, 0, 0), unknown_1254(0), unknown_1270(0), unknown_1484(0), unknown_1488(1), unknown_148c(0), unknown_1490(0),
      unknown_1494(0), unknown_1498(unknown_rect_ab6320), unknown_14a8(0), unknown_14ac(0), unknown_14b0(0),
      unknown_14b8(false), unknown_14b9(false), unknown_14d0(-1), unknown_14d4(false), unknown_14d5(false),
      unknown_14d6(false), unknown_14d8(unknown_rect_ab6320), unknown_14f8(0), unknown_14fc(0)
{
    unknown_1254 = Make_Table(256, 10);
    unknown_1258.Set_Growth_Step(500);
    unknown_14bc.Unknown_00405BF0();
}
