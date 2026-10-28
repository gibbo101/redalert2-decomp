// bool TActionClass::unknown_func_6b0d30(...) (0x006B0D30)
// Passes Data to 0x005A07F0 with -1, 1, 1, 1; always true.
#include "shared/taction.hpp"
#include "shared/team.hpp"

bool TActionClass::unknown_func_6b0d30(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Unknown_005A07F0(Data, -1, 1, 1, 1);
    return true;
}
