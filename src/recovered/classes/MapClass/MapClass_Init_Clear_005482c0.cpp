// void MapClass::Init_Clear() (0x005482C0, slot 7)
// Resets the map between scenarios: the two unidentified resets around the
// base screen's Init_Clear, every +0x154 entry's cell and stopped countdown,
// +0x144 back to 13 and the +0x1154 counter. Its trace strings name it.
#include "shared/map.hpp"
// @ref ?unknown_cell_a6f238@@3VCell@@A=00a6f238
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_481fb0@@YAXXZ=00481fb0
// @ref ?unknown_839c6c@@3PAVUnknown839C6C@@A=00839c6c
// @ref ?Unknown_00776160@Unknown839C6C@@QAEXH@Z=00776160
// @ref ?unknown_8315b4@@3PAVUnknown8315B4@@A=008315b4
// @ref ?Unknown_00411050@Unknown8315B4@@QAEXH@Z=00411050
// @ref ?Init_Clear@GScreenClass@@UAEXXZ=004e0980
// @ref ?Frame@@3HA=00a40d2c

void MapClass::Init_Clear()
{
    Debug_Printf("MapClass::Init_Clear entry\n");
    unknown_481fb0();
    unknown_839c6c->Unknown_00776160(0xFFFF);
    unknown_8315b4->Unknown_00411050(0x7F);
    unknown_481fb0();
    GScreenClass::Init_Clear();
    unknown_481fb0();
    for (int index = 0; index < 256; index++) {
        UnknownMapEntry154 &entry = unknown_154[index];
        entry.Cell = unknown_cell_a6f238;
        entry.Timer.Stop();
    }
    unknown_144 = 13;
    unknown_1154 = false;
    Debug_Printf("MapClass::Init_Clear done\n");
}
// @ref ??_C@_0BM@GHCI@MapClass?3?3Init_Clear?5entry?6?$AA@=007e07d4
// @ref ??_C@_0BL@IEID@MapClass?3?3Init_Clear?5done?6?$AA@=007e07b8
