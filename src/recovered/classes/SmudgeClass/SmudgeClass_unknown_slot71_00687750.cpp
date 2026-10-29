// bool SmudgeClass::unknown_slot71(int arg1) (0x00687750)
// After the base handling succeeds for modes 1 and 3, marks the smudge's
// cells (SmudgeTypeClass::Place, when the cells allow it or placement is
// forced) and removes the object (slot 60).
#include "shared/smudge.hpp"
// @ref ?unknown_slot71@ObjectClass@@UAE_NH@Z=005d4160
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?Can_Place@SmudgeTypeClass@@QBE_NABVCell@@_N@Z=00688a40
// @ref ?Place@SmudgeTypeClass@@QBEXABVCell@@@Z=00688b40

bool SmudgeClass::unknown_slot71(int arg1)
{
    if (ObjectClass::unknown_slot71(arg1) && (arg1 == 1 || arg1 == 3)) {
        Cell cell = Cell(unknown_slot104());
        if (unknown_a40774 > 0 || unknown_a40d13 || Class->Can_Place(cell, true)) {
            Class->Place(cell);
        }
        unknown_74 = false;
        unknown_slot60();
        return true;
    }
    return false;
}
