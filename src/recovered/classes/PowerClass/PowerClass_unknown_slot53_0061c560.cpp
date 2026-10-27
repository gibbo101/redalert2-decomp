// void PowerClass::unknown_slot53() (0x0061C560, slot 53)
// After the radar's shapes, loads the power bar shape "POWERP.SHP".
#include "shared/power.hpp"
// @ref ?unknown_slot53@RadarClass@@UAEXXZ=0062f310
// @ref ?Unknown_Load_Shape_00495270@@YIPBXPBDAA_N@Z=00495270
// @ref ?PowerShape@PowerClass@@2PBXB=00a7691c
// @ref ?PowerShapeAllocated@PowerClass@@2_NA=00a76920

void PowerClass::unknown_slot53()
{
    RadarClass::unknown_slot53();
    PowerShape = Unknown_Load_Shape_00495270("POWERP.SHP", PowerShapeAllocated);
}
// @ref ??_C@_0L@IPOE@POWERP?4SHP?$AA@=007ebf0c
