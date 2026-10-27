// bool TActionClass::unknown_start_mission_timer(...) (0x006B0A20)
// If the session mission timer is stopped, starts it and flags the tab bar for a redraw; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_006A17B0@TabClass@@QAEXXZ=006a17b0


bool TActionClass::unknown_start_mission_timer(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_id_source_a3d290->MissionTimer.Started == -1) {
        unknown_id_source_a3d290->MissionTimer.Start();
        Map.Unknown_006A17B0();
    }
    return true;
}
