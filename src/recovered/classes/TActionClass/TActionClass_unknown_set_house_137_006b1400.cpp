// bool TActionClass::unknown_set_house_137(...) (0x006B1400)
// Sets HouseClass +0x137 of the house of type Data.Value; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760

bool TActionClass::unknown_set_house_137(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data.Value != -1) {
        HouseClass::As_Pointer(Data.Value)->unknown_137 = true;
    }
    return true;
}


