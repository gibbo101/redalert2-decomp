// void SpotLightClass::Update_All() (0x005DD6D0)
#include "shared/spot_light.hpp"

void SpotLightClass::Update_All()
{
    for (int index = unknown_SpotLightClass_list_00a731c0.Count() - 1; index >= 0; index--) {
        unknown_SpotLightClass_list_00a731c0[index]->AI();
    }
}
