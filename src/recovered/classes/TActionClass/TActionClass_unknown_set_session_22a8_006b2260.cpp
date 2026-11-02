// bool TActionClass::unknown_set_session_22a8(...) (0x006B2260)
// Sets the ID source's +0x22A8 (the lighting ambient) to Data.Value and copies it
// to +0x22B0 unless 0x0051FC50 holds; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/team.hpp"
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50

bool TActionClass::unknown_set_session_22a8(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_id_source_a3d290->unknown_22a8 = Data.Value;
    if (!Unknown_0051FC50()) {
        unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->unknown_22a8;
    }
    return true;
}


