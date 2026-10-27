// RulesClass::Warheads (0x0064C160)
// @ref ??_C@_08NGFH@Warheads?$AA@=007eef10
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a WarheadTypeClass for every name listed in [Warheads].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/warhead_type.hpp"

bool RulesClass::Warheads(CCINIClass &ini)
{
    int count = ini.Entry_Count("Warheads");
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String("Warheads", ini.Get_Entry("Warheads", index), "", buffer, sizeof(buffer))) {
            WarheadTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
