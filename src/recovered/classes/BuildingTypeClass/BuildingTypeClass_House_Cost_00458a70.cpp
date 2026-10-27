// BuildingType cost adjustments reconstructed from the exact target.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/building_type.hpp"
#include "shared/unit.hpp"
#include "shared/unit_type.hpp"
#include "shared/rules.hpp"
#include "shared/aircraft_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// Genuine mathematical clamp; no original-address binding.

// Maximum_Cost is defined with Raw_Cost earlier in this whole class unit.
template<class T> inline T Maximum_Cost(T first,T second);

int BuildingTypeClass::unknown_slot33(int house) const
{
    int value=TechnoTypeClass::unknown_slot33(house);
    TechnoTypeClass *first_type=Rules->PadAircraft[0];
    if(this==first_type->Dock[0] && !Rules->unknown_142c) {
        int average=(int)((unsigned int)Rules->PadAircraft[0]->unknown_slot33(house)+(unsigned int)Rules->PadAircraft[1]->unknown_slot33(house))/2;
        value=(int)((unsigned int)value+(unsigned int)average);
    }
    if(FreeUnit) {
        value=(int)((unsigned int)value+(unsigned int)FreeUnit->unknown_slot33(house));
        return Maximum_Cost(value,0);
    }
    return value;
}
