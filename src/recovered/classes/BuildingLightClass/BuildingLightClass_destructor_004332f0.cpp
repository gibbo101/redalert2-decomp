// BuildingLightClass::~BuildingLightClass() (0x004332F0)
// Takes the light off the map (slot 52, called directly) and out of BuildingLights.
#include "shared/building_light.hpp"
// @ref ??1ObjectClass@@UAE@XZ=005d2530
// @ref ?unknown_slot52@ObjectClass@@UAE_NXZ=005d3700
// @ref ?Remove@UnknownList832470@@QAEXPAVObjectClass@@@Z=0053e370
// @ref ?unknown_list_832470@@3VUnknownList832470@@A=00832470
// @ref ?BuildingLights@@3V?$DynamicVectorClass@PAVBuildingLightClass@@@@A=00866220

BuildingLightClass::~BuildingLightClass()
{
    unknown_slot52();
    BuildingLights.Delete(this);
}
