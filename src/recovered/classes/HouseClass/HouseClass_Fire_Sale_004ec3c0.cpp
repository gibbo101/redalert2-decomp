// HRESULT __stdcall HouseClass::Fire_Sale() (0x004EC3C0)
// Sells every building of the house (IHouse).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

HRESULT __stdcall HouseClass::Fire_Sale()
{
    if (CurBuildings > 0) {
        int count = Buildings.Count();
        for (int index = 0; index < count; index++) {
            UnknownBuildingView *building = (UnknownBuildingView *)Buildings[index];
            if (building != 0 && !building->unknown_76 && building->Strength > 0) {
                building->unknown_slot98(1);
            }
        }
        return S_OK;
    }
    return 1;   // S_FALSE: nothing to sell
}
