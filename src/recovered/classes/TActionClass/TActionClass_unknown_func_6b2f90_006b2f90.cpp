// bool TActionClass::unknown_func_6b2f90(...) (0x006B2F90)
// Passes Data to 0x0065C1F0 (the radar movie's flag handler); always true.
#include "shared/taction.hpp"
#include "shared/unknown_globals.hpp"

bool TActionClass::unknown_func_6b2f90(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Unknown_0065C1F0(Data);
    return true;
}
