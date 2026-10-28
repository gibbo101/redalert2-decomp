// bool TActionClass::unknown_func_6b2f30(...) (0x006B2F30)
// Passes Data to every team of the team type at +0x30 (0x006C0110); always true.
#include "shared/taction.hpp"
#include "shared/team_type.hpp"

bool TActionClass::unknown_func_6b2f30(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_30 != 0) {
        ((TeamTypeClass *)unknown_30)->unknown_func_6c0110(Data);
    }
    return true;
}
