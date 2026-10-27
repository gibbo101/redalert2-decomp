// bool TActionClass::unknown_set_local_variable(...) (0x006B0630)
// Sets local variable Data (UnknownIDSource::unknown_6612c0); always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_6612c0@UnknownIDSource@@QAE_NI_N@Z=006612c0

bool TActionClass::unknown_set_local_variable(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_id_source_a3d290->unknown_6612c0(Data, true);
    return true;
}
