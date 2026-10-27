// bool TActionClass::unknown_make_enemy(...) (0x006B0500)
// Makes the action's house and the house of type Data enemies of each other (both directions, silent); always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760
// @ref ?Make_Enemy@HouseClass@@QAEXPAV1@_N@Z=004e5a70

bool TActionClass::unknown_make_enemy(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data != -1) {
        HouseClass *other = HouseClass::As_Pointer(Data);
        house->Make_Enemy(other, false);
        other->Make_Enemy(house, false);
    }
    return true;
}
