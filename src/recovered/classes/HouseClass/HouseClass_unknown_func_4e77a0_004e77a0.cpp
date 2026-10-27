// bool HouseClass::unknown_func_4e77a0(ObjectClass *object, bool arg2) (0x004E77A0)
// Replaces the object kept at +0x5308 (releasing the old one through
// 0x004E7580) and marks the new one with the house type.
#include "shared/techno.hpp"

// UnitClass as far as this unit calls it (view).
struct UnknownUnitView {
    bool unknown_func_7049c0(int house_type);   // 0x007049C0
};

bool HouseClass::unknown_func_4e77a0(ObjectClass *object, bool arg2)
{
    if (object != 0 && !object->unknown_76) {
        unknown_func_4e7580(unknown_5308, arg2);
        ((UnknownUnitView *)object)->unknown_func_7049c0(Type->House);
        unknown_5308 = object;
        return true;
    }
    return false;
}
