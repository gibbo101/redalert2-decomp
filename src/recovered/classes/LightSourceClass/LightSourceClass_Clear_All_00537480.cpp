// void LightSourceClass::Clear_All() (0x00537480): deletes every light and
// every pending cell, with cell updates suspended meanwhile.
#include "shared/light_source.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_7df630@@3_NA=007df630

void LightSourceClass::Clear_All()
{
    unknown_flag_7df630 = false;
    while (unknown_LightSourceClass_list_00a6e818.Count() != 0) {
        LightSourceClass *light = unknown_LightSourceClass_list_00a6e818[0];
        if (light != 0) {
            delete light;
        }
        unknown_LightSourceClass_list_00a6e818.Delete(0);
    }
    while (PendingCellClass::Array.Count() != 0) {
        delete PendingCellClass::Array[0];
        PendingCellClass::Array.Delete(0);
    }
    unknown_flag_7df630 = true;
}
