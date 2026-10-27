// BuildingType cost adjustments reconstructed from the exact target.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/building_type.hpp"
#include "shared/unit.hpp"
#include "shared/unit_type.hpp"
#include "shared/rules.hpp"
#include "shared/aircraft_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// Genuine mathematical clamp; no original-address binding.
template<class T> inline T Maximum_Cost(T first,T second) { return first>second ? first : second; }

int BuildingTypeClass::Raw_Cost() const
{
    int value=TechnoTypeClass::Raw_Cost();
    TechnoTypeClass *first_type=Rules->PadAircraft[0];
    if(this==first_type->Dock[0] && !Rules->unknown_142c) {
        int second_cost=Rules->PadAircraft[1]->Raw_Cost();
        int first_cost=first_type->Raw_Cost();
        int average=(int)((unsigned int)first_cost+(unsigned int)second_cost)/2;
        value=(int)((unsigned int)value-(unsigned int)average);
    }
    if(FreeUnit) {
        value=(int)((unsigned int)value-(unsigned int)FreeUnit->Raw_Cost());
        return Maximum_Cost(value,0);
    }
    return value;
}
