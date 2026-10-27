// void ScriptTypeClass::Read_Scenario_INI(CCINIClass &ini, int is_global) (0x00668CE0)
// Creates (or finds) every script type listed in [ScriptTypes] and reads
// its own section.
#include "shared/script.hpp"
// @ref ??_C@_0M@MFIC@ScriptTypes?$AA@=007f2bc8
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??2@YAPAXI@Z=00782017

void __fastcall ScriptTypeClass::Read_Scenario_INI(CCINIClass &ini, int is_global)
{
    char buffer[24];

    int count = ini.Entry_Count("ScriptTypes");
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry("ScriptTypes", index);
        if (ini.Get_String("ScriptTypes", entry, "", buffer, sizeof(buffer)) > 0) {
            ScriptTypeClass *script = Find_Or_Make(buffer);
            script->Read_INI(ini);
            script->IsGlobal = is_global;
        }
    }
}
