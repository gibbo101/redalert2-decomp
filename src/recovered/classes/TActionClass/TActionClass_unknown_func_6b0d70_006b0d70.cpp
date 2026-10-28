// bool TActionClass::unknown_func_6b0d70(...) (0x006B0D70)
// Plays sound Data at full volume (priority 0x2000); always true.
#include "shared/taction.hpp"
#include "shared/techno.hpp"

bool TActionClass::unknown_func_6b0d70(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Voc_Play(Data, 1.0f, 0x2000, 0);
    return true;
}
