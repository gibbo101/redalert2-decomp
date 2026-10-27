// float HouseClass::unknown_func_4f5a70(TechnoTypeClass *type) (0x004F5A70)
// The owner country's build time multiplier for the type's kind (infantry, vehicle,
// aircraft, building or, for a defence building (+0xBA0 == 5), defence); 1 otherwise.
// @ref __real@4@3fff8000000000000000=0079b7f8
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

float HouseClass::unknown_func_4f5a70(TechnoTypeClass *type)
{
    switch (type->Kind_Of()) {
    case 16:
        return Type->unknown_0x134;
    case 40:
        return Type->unknown_0x138;
    case 3:
        return Type->unknown_0x13C;
    case 7:
        if (((UnknownBuildingTypeBA0View const *)type)->unknown_ba0 == 5) {
            return Type->unknown_0x144;
        }
        return Type->unknown_0x140;
    }
    return 1.0f;
}
