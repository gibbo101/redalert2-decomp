// void __fastcall AITriggerTypeClass::Write_Scenario_INI(CCINIClass &ini, int is_global) (0x0041D6F0)
// Clears the AI trigger section (and every section its entries name), writes
// the types whose global flag (unknown_9c) matches, and for the scenario
// (not global) list rewrites the enable section from each type's flag.
#include "shared/ai_trigger_type.hpp"
// @ref ?unknown_section_79b748@@3PBDB=0079b748
// @ref ?unknown_section_79b74c@@3PBDB=0079b74c
// @ref ?AITriggerTypes@@3V?$DynamicVectorClass@PAVAITriggerTypeClass@@@@A=00a3d260
// @ref ?Entry_Count@INIClass@@QBEHPBD@Z=0050cb00
// @ref ?Get_Entry@INIClass@@QBEPBDPBDH@Z=0050ce00
// @ref ?Clear@INIClass@@QAE_NPBD0@Z=0050b9a0
// @ref ?Put_Bool@INIClass@@QAE_NPBD0_N@Z=0050f380

void __fastcall AITriggerTypeClass::Write_Scenario_INI(CCINIClass &ini, int is_global)
{
    char buffer[32];
    int count = ini.Entry_Count(unknown_section_79b748);
    int index;
    for (index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_section_79b748, index);
        ini.Get_String(unknown_section_79b748, entry, unknown_string_83c55c, buffer, sizeof(buffer));
        ini.Clear(buffer, 0);
    }
    ini.Clear(unknown_section_79b748, 0);

    for (index = 0; index < AITriggerTypes.Count(); index++) {
        AITriggerTypeClass *type = AITriggerTypes[index];
        if (type->unknown_9c == is_global) {
            type->Write_INI(ini);
        }
    }

    if (!is_global) {
        ini.Clear(unknown_section_79b74c, 0);
        for (index = 0; index < AITriggerTypes.Count(); index++) {
            AITriggerTypeClass *type = AITriggerTypes[index];
            ini.Put_Bool(unknown_section_79b74c, type->ID, type->unknown_a4);
        }
    }
}
