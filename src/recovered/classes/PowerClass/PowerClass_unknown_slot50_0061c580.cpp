// void PowerClass::unknown_slot50() (0x0061C580, slot 50)
// After the radar's, frees the power bar shape when it was loaded.
#include "shared/power.hpp"
// @ref ?unknown_slot50@RadarClass@@UAEXXZ=0062f210
// @ref ?PowerShape@PowerClass@@2PBXB=00a7691c
// @ref ?PowerShapeAllocated@PowerClass@@2_NA=00a76920
// @ref ??3@YAXPAX@Z=00781d3b

void PowerClass::unknown_slot50()
{
    RadarClass::unknown_slot50();
    if (PowerShapeAllocated) {
        operator delete((void *)PowerShape);
        PowerShapeAllocated = false;
    }
}
