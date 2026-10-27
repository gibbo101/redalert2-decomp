// void __fastcall TriggerTypeClass::Write_Scenario_INI(CCINIClass &ini) (0x006EEAA0)
// Clears the [Triggers], [Events] and [Actions] sections (and every section
// their entries name) and writes every trigger type. The entry values are
// always looked up under [Triggers].
#include "shared/trigger_type.hpp"
// @ref ?unknown_triggers_section_7ada50@@3PBDB=007ada50
// @ref ?unknown_actions_section_7ada54@@3PBDB=007ada54
// @ref ?unknown_events_section_7ada58@@3PBDB=007ada58
// @ref ?Entry_Count@INIClass@@QBEHPBD@Z=0050cb00
// @ref ?Get_Entry@INIClass@@QBEPBDPBDH@Z=0050ce00
// @ref ?Clear@INIClass@@QAE_NPBD0@Z=0050b9a0

void __fastcall TriggerTypeClass::Write_Scenario_INI(CCINIClass &ini)
{
    char buffer[32];
    int count = ini.Entry_Count(unknown_triggers_section_7ada50);
    int index;
    for (index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_triggers_section_7ada50, index);
        ini.Get_String(unknown_triggers_section_7ada50, entry, unknown_string_83c55c, buffer, sizeof(buffer));
        ini.Clear(buffer, 0);
    }
    ini.Clear(unknown_triggers_section_7ada50, 0);

    count = ini.Entry_Count(unknown_events_section_7ada58);
    for (index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_events_section_7ada58, index);
        ini.Get_String(unknown_triggers_section_7ada50, entry, unknown_string_83c55c, buffer, sizeof(buffer));
        ini.Clear(buffer, 0);
    }
    ini.Clear(unknown_events_section_7ada58, 0);

    count = ini.Entry_Count(unknown_actions_section_7ada54);
    for (index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_actions_section_7ada54, index);
        ini.Get_String(unknown_triggers_section_7ada50, entry, unknown_string_83c55c, buffer, sizeof(buffer));
        ini.Clear(buffer, 0);
    }
    ini.Clear(unknown_actions_section_7ada54, 0);

    for (index = 0; index < TriggerTypes.Count(); index++) {
        TriggerTypes[index]->Write_INI(ini);
    }
}
