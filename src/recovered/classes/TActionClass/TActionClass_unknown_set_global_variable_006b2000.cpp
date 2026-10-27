// bool TActionClass::unknown_set_global_variable(...) (0x006B2000)
// Sets global variable Data (UnknownIDSource::unknown_661560); always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_661560@UnknownIDSource@@QAE_NI_N@Z=00661560

bool TActionClass::unknown_set_global_variable(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_id_source_a3d290->unknown_661560(Data, true);
    return true;
}
