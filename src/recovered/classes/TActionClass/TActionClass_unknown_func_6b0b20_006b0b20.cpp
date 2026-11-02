// bool TActionClass::unknown_func_6b0b20(...) (0x006B0B20)
// Takes Data.Value quarter minutes (15 frames each) from the mission timer (not
// below zero), restarting it, and has the tab redraw it; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"

bool TActionClass::unknown_func_6b0b20(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_id_source_a3d290->MissionTimer <= Data.Value * 15) {
        unknown_id_source_a3d290->MissionTimer = 0;
    } else {
        unknown_id_source_a3d290->MissionTimer = unknown_id_source_a3d290->MissionTimer - Data.Value * 15;
    }
    Map.Unknown_006A17B0();
    return true;
}


