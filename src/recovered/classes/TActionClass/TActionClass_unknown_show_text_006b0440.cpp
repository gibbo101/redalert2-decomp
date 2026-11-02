// Text style type/bitwise operation hypothesis from Westwood headers; native caller passes0x4046.
enum TextPrintType { TPF_6PT_GRAD = 6, TPF_FULLSHADOW = 0x40, TPF_USE_GRAD_PAL = 0x4000 };
inline TextPrintType operator|(TextPrintType left, TextPrintType right)
{
    return static_cast<TextPrintType>(static_cast<int>(left) | static_cast<int>(right));
}
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
    char const *text = Get_Text();
    UnknownIDSource *scenario = unknown_id_source_a3d290;
    int color_scheme = scenario->unknown_2239 ? 2 : 1;
    int color = unknown_session_a3d298.Unknown_006715D0(color_scheme);
    if (text != 0) {
        unknown_messages_a3dc70.Add_Message(0, 0, StringTable::Load_String(text, 0, "D:\\Ra2\\TAction.CPP", 0x62E), color, TextPrintType(TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_FULLSHADOW), (int)(Rules->MessageDelay * 900.0), 0);
    }
    return true;
}


