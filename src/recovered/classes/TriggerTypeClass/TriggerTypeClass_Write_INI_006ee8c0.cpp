// bool TriggerTypeClass::Write_INI(CCINIClass &ini) const (0x006EE8C0, slot 26)
// The inverse of Read_INI: the [Triggers] line, then the [Events] and
// [Actions] lines (count, then each entry appended after a comma).
#include "shared/trigger_type.hpp"
// @ref ?unknown_triggers_section_7ada50@@3PBDB=007ada50
// @ref ?unknown_actions_section_7ada54@@3PBDB=007ada54
// @ref ?unknown_events_section_7ada58@@3PBDB=007ada58
// @ref ??_C@_0BI@BHOE@?$CFs?0?$CFs?0?$CFs?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?$AA@=007f8610
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ?Build_INI_Entry@TEventClass@@QBEXPAD@Z=006e68b0
// @ref ?Build_INI_Entry@TActionClass@@QBEXPAD@Z=006ad640


extern "C" char *__cdecl strcat(char *dest, char const *source);
#pragma intrinsic(strcat)

extern char const *unknown_triggers_section_7ada50;
extern char const *unknown_actions_section_7ada54;
extern char const *unknown_events_section_7ada58;

bool TriggerTypeClass::Write_INI(CCINIClass &ini) const
{
    char buffer[512];
    sprintf(buffer, "%s,%s,%s,%d,%d,%d,%d,%d",
        unknown_a4 != 0 ? (char const *)unknown_a4->ID : "<none>",
        Next != 0 ? (char const *)Next->ID : "<none>",
        (char const *)Name, IsEnabled ? 0 : 1, IsEasy ? 1 : 0, IsNormal ? 1 : 0, IsHard ? 1 : 0, unknown_a0 ? 1 : 0);
    ini.Put_String(unknown_triggers_section_7ada50, ID, buffer);

    int count = 0;
    TEventClass *event;
    for (event = Events; event != 0; event = event->Next) {
        count++;
    }
    sprintf(buffer, "%d", count);
    for (event = Events; event != 0; event = event->Next) {
        strcat(buffer, ",");
        event->Build_INI_Entry(buffer);
    }
    ini.Put_String(unknown_events_section_7ada58, ID, buffer);

    count = 0;
    TActionClass *action;
    for (action = Actions; action != 0; action = action->Next) {
        count++;
    }
    sprintf(buffer, "%d", count);
    for (action = Actions; action != 0; action = action->Next) {
        strcat(buffer, ",");
        action->Build_INI_Entry(buffer);
    }
    ini.Put_String(unknown_actions_section_7ada54, ID, buffer);
    return true;
}
