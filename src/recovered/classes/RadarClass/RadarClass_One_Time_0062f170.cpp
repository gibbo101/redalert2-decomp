// void RadarClass::One_Time() (0x0062F170, slot 5)
// Fixes the radar's screen metrics, runs the display's one-time setup,
// places the radar button and looks up the incoming-transmission voice.
#include "shared/radar.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?One_Time@DisplayClass@@UAEXXZ=00498b70
// @ref ?RadarButton@RadarClass@@2VRTacticalClass@@A=00ab6478
// @ref ?Unknown_00716640@@YIHPBD@Z=00716640

void RadarClass::One_Time()
{
    Debug_Printf("RadarClass::One_Time()\n");
    unknown_11fc = 140;
    unknown_11e0 = 0;
    unknown_11e4 = 16;
    unknown_11e8 = 48;
    unknown_1200 = 108;
    unknown_11f4 = unknown_11fc;
    unknown_11f8 = unknown_1200;
    unknown_11f0 = 49;
    DisplayClass::One_Time();
    RadarButton.Y = unknown_11f0;
    RadarButton.Width = unknown_11fc;
    RadarButton.Height = unknown_1200;
    RadarButton.Flags = 0xDF;
    unknown_14d0 = Unknown_00716640("EVA_IncomingTransmission");
}
// @ref ??_C@_0BI@FJEE@RadarClass?3?3One_Time?$CI?$CJ?6?$AA@=007ee14c
// @ref ??_C@_0BJ@IAHO@EVA_IncomingTransmission?$AA@=007ee130
