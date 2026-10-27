// bool BuildingLightClass::unknown_slot53(CoordStruct const *coord, int dir) (0x004347E0, slot 53)
// ObjectClass's slot 53, then submits the light to the list at 0x00832470.
#include "shared/building_light.hpp"
// @ref ?unknown_slot53@ObjectClass@@UAE_NPBUCoordStruct@@H@Z=005d3890
// @ref ?unknown_list_832470@@3VUnknownList832470@@A=00832470
// @ref ?Submit@UnknownList832470@@QAE_NPAVObjectClass@@_N@Z=0053e330

bool BuildingLightClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    if (ObjectClass::unknown_slot53(coord, dir)) {
        unknown_list_832470.Submit(this, false);
        return true;
    }
    return false;
}
