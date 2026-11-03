#include "shared/building_light.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref _unknown_geometry_l=0084ea28
// @ref ??0UnknownCoord434820@@QAE@HHH@Z=00434820
// @ref ?BuildingLights@@3V?$DynamicVectorClass@PAVBuildingLightClass@@@@A=00866220
// @ref ??_7BuildingLightClass@@6BIPersistStream@@@=0079c7e0
// @ref ??_7BuildingLightClass@@6BIRTTITypeInfo@@@=0079c7c4
// @ref ??_7BuildingLightClass@@6BINoticeSink@@@=0079c7bc
// @ref ??_7BuildingLightClass@@6BINoticeSource@@@=0079c7b4
// @ref ?unknown_slot53@ObjectClass@@UAE_NPBUCoordStruct@@H@Z=005d3890
// @ref ?Submit@UnknownList832470@@QAE_NPAVObjectClass@@_N@Z=0053e330
// @ref ?Set_Behavior@BuildingLightClass@@QAEXH@Z=00434370
BuildingLightClass::BuildingLightClass(TechnoClass *owner) :
    unknown_98(0),
    unknown_a0(unknown_geometry_l),
    unknown_ac(unknown_geometry_l),
    unknown_b8(0),
    unknown_c0(false),
    Behavior(0),
    Following(0),
    Owner(owner)
{
    BuildingLights.Add(this);
    if (owner != 0) {
        unknown_func_4341d0(owner);
        BuildingLightClass::unknown_slot53(&CoordStruct(Coord), 0);
        Set_Behavior(1);
        unknown_c0 = BuildingLights.ID(this) % 2 != 0;
    }
}
