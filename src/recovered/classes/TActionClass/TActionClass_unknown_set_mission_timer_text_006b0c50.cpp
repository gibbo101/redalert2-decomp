// bool TActionClass::unknown_set_mission_timer_text(...) (0x006B0C50)
// Sets the mission timer text from the action's text (the string table entry and its label; the empty text and label without one) and has the tab redraw it; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/abstract_type.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/string_table.hpp"
#include "shared/map_view.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_0BD@GLBG@D?3?2Ra2?2TAction?4CPP?$AA@=007f6bd0

bool TActionClass::unknown_set_mission_timer_text(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    char const *text = Get_Text();
    FixedString<32> label(text);
    if (text != 0) {
        unknown_id_source_a3d290->MissionTimerText = StringTable::Load_String(text, 0, "D:\\Ra2\\TAction.CPP", 0x802);
        unknown_id_source_a3d290->MissionTimerLabel = label;
    } else {
        unknown_id_source_a3d290->MissionTimerText = unknown_empty_wide_839d4c;
        FixedString<32> empty_label(unknown_string_83c55c);
        unknown_id_source_a3d290->MissionTimerLabel = empty_label;
    }
    Map.Unknown_006A17B0();
    return true;
}


