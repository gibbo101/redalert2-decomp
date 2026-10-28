// bool TActionClass::unknown_func_6b1a80(...) (0x006B1A80)
// Unless Unknown_0051FC50 holds (then false), calls 0x0051F930 with Data,
// the rules value at +0x13E8 and the zero cell (as TeamClass 0x006BC460);
// true.
#include "shared/taction.hpp"
#include "shared/team.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051F930@@YIXHHVCell@@H@Z=0051f930

bool TActionClass::unknown_func_6b1a80(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Unknown_0051FC50()) {
        return false;
    }
    Unknown_0051F930(Data, Rules->unknown_13e8, unknown_geometry_k, 0);
    return true;
}
