// void __fastcall AITriggerTypeClass::Read_Scenario_INI(CCINIClass &ini, int is_global) (0x0041D540)
// Makes (or finds) and reads the AI trigger type of every entry, marks it
// global or not (enabled outright when global); for the scenario list the
// enable section then switches the existing types on or off (all on when the
// game mode is not 0).
#include "shared/ai_trigger_type.hpp"
#include "shared/object.hpp"
// @ref ?unknown_section_79b748@@3PBDB=0079b748
// @ref ?unknown_section_79b74c@@3PBDB=0079b74c
// @ref ?AITriggerTypes@@3V?$DynamicVectorClass@PAVAITriggerTypeClass@@@@A=00a3d260
// @ref ?Entry_Count@INIClass@@QBEHPBD@Z=0050cb00
// @ref ?Get_Entry@INIClass@@QBEPBDPBDH@Z=0050ce00
// @ref ?Get_Bool@INIClass@@QBE_NPBD0_N@Z=0050f410
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ??0AITriggerTypeClass@@QAE@PBD@Z=0041c5c0
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec

// The named AI trigger type, or 0 (no type is made).
static inline AITriggerTypeClass *Find_AI_Trigger(char const *name)
{
    for (int index = 0; index < AITriggerTypes.Count(); index++) {
        if (!_stricmp(AITriggerTypes[index]->ID, name)) {
            return AITriggerTypes[index];
        }
    }
    return 0;
}

void __fastcall AITriggerTypeClass::Read_Scenario_INI(CCINIClass &ini, int is_global)
{
    int count = ini.Entry_Count(unknown_section_79b748);
    int index;
    for (index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_section_79b748, index);
        AITriggerTypeClass *type = Find_Or_Make(entry);
        if (type != 0) {
            type->Read_INI(ini);
            type->unknown_9c = is_global;
        }
        if (is_global == 1) {
            type->unknown_a4 = true;
        }
    }

    if (is_global == 0) {
        count = ini.Entry_Count(unknown_section_79b74c);
        for (index = 0; index < count; index++) {
            char const *entry = ini.Get_Entry(unknown_section_79b74c, index);
            AITriggerTypeClass *type = Find_AI_Trigger(entry);
            if (type != 0) {
                if (ini.Get_Bool(unknown_section_79b74c, entry, false) || unknown_game_mode_a3d298 != 0) {
                    type->unknown_a4 = true;
                } else {
                    type->unknown_a4 = false;
                }
            }
        }
    }
}
