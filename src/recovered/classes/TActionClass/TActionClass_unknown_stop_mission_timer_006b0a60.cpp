// bool TActionClass::unknown_stop_mission_timer(...) (0x006B0A60)
// If the mission timer runs, stops it and flags the tab bar for a redraw; always true (Red Alert's TACTION_STOP_TIMER).
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_006A17B0@TabClass@@QAEXXZ=006a17b0

bool TActionClass::unknown_stop_mission_timer(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_id_source_a3d290->MissionTimer.Started != -1) {
        unknown_id_source_a3d290->MissionTimer.Stop();
        Map.Unknown_006A17B0();
    }
    return true;
}


