// int BuildingClass::unknown_slot166() (0x00449110, slot 166)
// For pip scale 2: 0 unless the type is a weeder, else the type's pips
// (slot 29) scaled by the owner's ratio (0x004E5240); otherwise the techno
// value.
#include "shared/building.hpp"
// @ref ?unknown_slot166@TechnoClass@@UAEHXZ=006d3ed0
// @ref ?unknown_func_4e5240@HouseClass@@QBENXZ=004e5240
// @ref __ftol=0077f110

int BuildingClass::unknown_slot166()
{
    BuildingTypeClass *type = Type;
    switch (type->PipScale) {
    case 2:
        if (type->Weeder) {
            double ratio = House->unknown_func_4e5240();
            return type->unknown_slot29() * ratio;
        }
        return 0;
    default:
        return TechnoClass::unknown_slot166();
    }
}
