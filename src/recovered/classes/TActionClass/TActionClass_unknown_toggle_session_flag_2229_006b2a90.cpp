// bool TActionClass::unknown_toggle_session_flag_2229(...) (0x006B2A90)
// Toggles the session byte +0x2229; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"


bool TActionClass::unknown_toggle_session_flag_2229(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_id_source_a3d290->unknown_2229 = !unknown_id_source_a3d290->unknown_2229;
    return true;
}
