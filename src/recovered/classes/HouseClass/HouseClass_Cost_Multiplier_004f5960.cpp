// float HouseClass::Cost_Multiplier(TechnoTypeClass const *type) (0x004F5960)
// The owner country's cost multiplier for the type's kind (infantry, vehicle,
// aircraft, building or, for a defence building (+0xBA0 == 5), defence); 1 otherwise.
// @ref __real@4@3fff8000000000000000=0079b7f8
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

float HouseClass::Cost_Multiplier(TechnoTypeClass const *type)
{
    switch (type->Kind_Of()) {
    case 16:
        return Type->unknown_0x114;
    case 40:
        return Type->unknown_0x118;
    case 3:
        return Type->unknown_0x11C;
    case 7:
        if (((UnknownBuildingTypeBA0View const *)type)->unknown_ba0 == 5) {
            return Type->unknown_0x124;
        }
        return Type->unknown_0x120;
    }
    return 1.0f;
}
