// void __fastcall TriggerTypeClass::Read_Scenario_INI(CCINIClass &ini) (0x006EE7F0)
// Makes (or finds) the trigger type of every [Triggers] entry and reads it.
#include "shared/trigger_type.hpp"
// @ref ?unknown_triggers_section_7ada50@@3PBDB=007ada50
// @ref ?Entry_Count@INIClass@@QBEHPBD@Z=0050cb00
// @ref ?Get_Entry@INIClass@@QBEPBDPBDH@Z=0050ce00
// @ref ??0TriggerTypeClass@@QAE@PBD@Z=006edeb0
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec

void __fastcall TriggerTypeClass::Read_Scenario_INI(CCINIClass &ini)
{
    int count = ini.Entry_Count(unknown_triggers_section_7ada50);
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_triggers_section_7ada50, index);
        TriggerTypeClass *type = Find_Or_Make(entry);
        type->Read_INI(ini);
    }
}
