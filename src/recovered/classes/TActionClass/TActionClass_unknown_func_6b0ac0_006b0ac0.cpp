// bool TActionClass::unknown_func_6b0ac0(...) (0x006B0AC0)
// Adds Data quarter minutes (15 frames each) to the mission timer, restarting
// it from the time left, and has the tab redraw it; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"

bool TActionClass::unknown_func_6b0ac0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_id_source_a3d290->MissionTimer = CDTimerClass<FrameTimerClass>(unknown_id_source_a3d290->MissionTimer.Value() + Data * 15);
    Map.Unknown_006A17B0();
    return true;
}
