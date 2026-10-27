// void RadarClass::Init_Clear() (0x0062F260, slot 7)
// Clears the display, then the radar's state and its two lists.
#include "shared/radar.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Init_Clear@DisplayClass@@UAEXXZ=00498be0

void RadarClass::Init_Clear()
{
    DisplayClass::Init_Clear();
    Debug_Printf("RadarClass::Init_Clear\n");
    unknown_14a8 = 0;
    unknown_14ac = 0;
    unknown_14b9 = false;
    unknown_14b8 = false;
    unknown_14f8 = 0;
    unknown_14d4 = false;
    unknown_14d5 = true;
    unknown_1220.Clear();
    unknown_1258.Clear();
    Debug_Printf("RadarClass::Init_Clear done\n");
}
// @ref ??_C@_0BI@DNAN@RadarClass?3?3Init_Clear?6?$AA@=007ee184
// @ref ??_C@_0BN@PPM@RadarClass?3?3Init_Clear?5done?6?$AA@=007ee164
