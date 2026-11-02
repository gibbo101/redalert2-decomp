// bool TActionClass::unknown_func_6b0ba0(...) (0x006B0BA0)
// Sets the mission timer to Data.Value quarter minutes (15 frames each) and starts
// it, clears its text and label, and has the tab redraw it; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/abstract_type.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/map_view.hpp"

bool TActionClass::unknown_func_6b0ba0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_id_source_a3d290->MissionTimer = Data.Value * 15;
    unknown_id_source_a3d290->MissionTimer.Start();
    unknown_id_source_a3d290->MissionTimerText = unknown_empty_wide_839d4c;
    FixedString<32> label(unknown_string_83c55c);
    unknown_id_source_a3d290->MissionTimerLabel = label;
    Map.Unknown_006A17B0();
    return true;
}


