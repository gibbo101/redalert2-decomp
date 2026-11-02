// bool TActionClass::unknown_make_ally(...) (0x006B04C0)
// Makes the action's house and the house of type Data.Value allies of each other (both directions, silent); always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760
// @ref ?Make_Ally@HouseClass@@QAEXPAV1@_N@Z=004e5660

bool TActionClass::unknown_make_ally(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data.Value != -1) {
        HouseClass *other = HouseClass::As_Pointer(Data.Value);
        house->Make_Ally(other, false);
        other->Make_Ally(house, false);
    }
    return true;
}


