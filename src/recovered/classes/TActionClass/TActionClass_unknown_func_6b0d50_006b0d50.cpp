// bool TActionClass::unknown_func_6b0d50(...) (0x006B0D50)
// Unknown_005A0920(Data.Value, false); always true.
#include "shared/taction.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Unknown_005A0920@@YIXH_N@Z=005a0920

bool TActionClass::unknown_func_6b0d50(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Unknown_005A0920(Data.Value, false);
    return true;
}


