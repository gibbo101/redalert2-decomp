// TechnoClass *AircraftClass::unknown_slot299(DynamicVectorClass<TechnoTypeClass *> const *types, int arg2, int arg3) (0x0041B1E0, slot 299)
// For airport-bound types keeps +0x5B4 while slot 150 (+0x258) answers 1
// for it with 15; otherwise replaces it with FootClass's answer for
// (types, 0, arg3).
#include "shared/aircraft.hpp"
// @ref ?unknown_slot299@FootClass@@UAEPAVTechnoClass@@PBV?$DynamicVectorClass@PAVTechnoTypeClass@@@@HH@Z=004cd920

TechnoClass *AircraftClass::unknown_slot299(DynamicVectorClass<TechnoTypeClass *> const *types, int arg2, int arg3)
{
    if (Type->AirportBound && unknown_5b4 != 0) {
        if (unknown_slot150(15, unknown_5b4) != 1) {
            unknown_5b4 = 0;
        } else {
            return unknown_5b4;
        }
    }
    unknown_5b4 = FootClass::unknown_slot299(types, 0, arg3);
    return unknown_5b4;
}
