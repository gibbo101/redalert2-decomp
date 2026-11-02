// bool TActionClass::unknown_set_house_136(...) (0x006B13C0)
// Sets +0x136 of the house of type Data.Value (none for -1); always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760

bool TActionClass::unknown_set_house_136(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data.Value != -1) {
        HouseClass::As_Pointer(Data.Value)->unknown_136 = true;
    }
    return true;
}


