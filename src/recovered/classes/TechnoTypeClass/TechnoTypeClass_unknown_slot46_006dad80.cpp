// int TechnoTypeClass::unknown_slot46(HouseClass *house, bool full) const (0x006DAD80)
// Sell value (hypothesis): Soylent= when set, else the house cost scaled by
// the rules refund factor (1.0 when full).
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Cost_Multiplier@HouseClass@@QAEMPBVTechnoTypeClass@@@Z=004f5960
// @ref __ftol=0077f110
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0

int TechnoTypeClass::unknown_slot46(HouseClass *house, bool full) const
{
    float percent = (float)Rules->unknown_13a0;
    if (full) {
        percent = 1.0f;
    }
    if (house) {
        float factor = house->Cost_Multiplier(this);
        if (Soylent) {
            return (int)(Soylent * factor);
        }
        int cost = (int)(Raw_Cost() * factor);
        if (house->Unknown_004F52F0()) {
            cost = (int)(cost * percent);
        }
        return cost;
    }
    return (int)(Raw_Cost() * percent);
}
