// RulesClass::Smudges (0x0064BFA0)
// @ref ?Find_Or_Make@SmudgeTypeClass@@SIPAV1@PBD@Z=006883d0
// @ref _RulesSection_SmudgeTypes=007a9088
// @ref ??_C@_0M@BCBF@SmudgeTypes?$AA@=007eec0c
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a SmudgeTypeClass for every name listed in [SmudgeTypes].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/smudge_type.hpp"

bool RulesClass::Smudges(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_SmudgeTypes);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_SmudgeTypes, ini.Get_Entry(RulesSection_SmudgeTypes, index), "", buffer, sizeof(buffer))) {
            SmudgeTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
