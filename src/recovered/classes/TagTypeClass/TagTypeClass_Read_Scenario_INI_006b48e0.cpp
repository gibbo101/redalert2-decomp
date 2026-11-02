// void __fastcall TagTypeClass::Read_Scenario_INI(CCINIClass &ini) (0x006B48E0)
// Makes (or finds) the tag type of every [Tags] entry, registers its ID for
// pointer fixups and reads it.
#include "shared/object.hpp"

void __fastcall TagTypeClass::Read_Scenario_INI(CCINIClass &ini)
{
    int count = ini.Entry_Count(unknown_tags_section_7ac770);
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_tags_section_7ac770, index);
        char buffer[24];
        if (ini.Get_String(unknown_tags_section_7ac770, entry, unknown_string_83c55c, buffer, sizeof(buffer)) > 0) {
            TagTypeClass *type = Find_Or_Make(entry);
            SwizzleManager.Here_I_Am(ahtoi(entry), type);
            type->Read_INI(ini);
        }
    }
}
