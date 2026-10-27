// RulesClass::Animations (0x0064C080)
// @ref ??_C@_0L@GJLI@Animations?$AA@=007f1668
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a AnimTypeClass for every name listed in [Animations].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/anim_type.hpp"

bool RulesClass::Animations(CCINIClass &ini)
{
    int count = ini.Entry_Count("Animations");
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String("Animations", ini.Get_Entry("Animations", index), "", buffer, sizeof(buffer))) {
            AnimTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
