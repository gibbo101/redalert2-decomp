// float HouseClass::unknown_func_4f58a0(TechnoTypeClass *type) (0x004F58A0)
// The owner country's armor multiplier for the type's kind (infantry, vehicle,
// aircraft, building or, for a defence building (+0xBA0 == 5), defence); 1 otherwise.
// @ref __real@4@3fff8000000000000000=0079b7f8
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

float HouseClass::unknown_func_4f58a0(TechnoTypeClass *type)
{
    switch (type->Kind_Of()) {
    case 16:
        return Type->unknown_0x100;
    case 40:
        return Type->unknown_0x104;
    case 3:
        return Type->unknown_0x108;
    case 7:
        if (((UnknownBuildingTypeBA0View const *)type)->unknown_ba0 == 5) {
            return Type->unknown_0x110;
        }
        return Type->unknown_0x10C;
    }
    return 1.0f;
}
