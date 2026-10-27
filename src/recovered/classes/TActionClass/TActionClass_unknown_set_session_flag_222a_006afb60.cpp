// bool TActionClass::unknown_set_session_flag_222a(...) (0x006AFB60)
// Copies the low byte of Data into the session byte +0x222B; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"

bool TActionClass::unknown_set_session_flag_222a(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_id_source_a3d290->unknown_222a = (char)Data;
    return true;
}
