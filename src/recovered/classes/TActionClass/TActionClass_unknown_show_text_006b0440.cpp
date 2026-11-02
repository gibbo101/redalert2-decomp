// bool TActionClass::unknown_show_text(...) (0x006B0440)
// Shows the action's text (when it has one) in the message list in the color slot 1 (2 when +0x2239 is set)
// for the rules' MessageDelay minutes; always true. The named rules pointer gives the original's eax load.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/rules.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/uicmnds.hpp"
#include "shared/session_state.hpp"
#include "shared/message_list.hpp"
// @ref ?Unknown_006715D0@UnknownSessionState@@QAEHH@Z=006715d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ??_C@_0BD@GLBG@D?3?2Ra2?2TAction?4CPP?$AA@=007f6bd0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0

bool TActionClass::unknown_show_text(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    UnknownIDSource *scenario = unknown_id_source_a3d290;
    char const *text = Get_Text();
    int color = unknown_session_a3d298.Unknown_006715D0(scenario->unknown_2239 ? 2 : 1);
    if (text != 0) {
        RulesClass *rules = Rules;
        unknown_messages_a3dc70.Add_Message(0, 0, StringTable::Load_String(text, 0, "D:\\Ra2\\TAction.CPP", 0x62E), color, 0x4046, (int)(rules->MessageDelay * 900.0), 0);
    }
    return true;
}
