// void SpotLightClass::Draw_All() (0x005DE2E0)
#include "shared/spot_light.hpp"
// @ref ?unknown_func_5ddb90@SpotLightClass@@QAEXXZ=005ddb90

void SpotLightClass::Draw_All()
{
    for (int index = unknown_SpotLightClass_list_00a731c0.Count() - 1; index >= 0; index--) {
        unknown_SpotLightClass_list_00a731c0[index]->unknown_func_5ddb90();
    }
}
