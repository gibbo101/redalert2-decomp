// RulesClass::Heap_Maximums (0x0064BA00)
// @ref ??_C@_07CGJA@Players?$AA@=007eef08
// @ref _RulesSection_Maximums=007a9060
// @ref ??_C@_08EDKN@Maximums?$AA@=007eec98
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"

bool RulesClass::Heap_Maximums(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_Maximums)) {
        MaxPlayers = ini.Get_Int(RulesSection_Maximums, "Players", MaxPlayers);
    }
    return true;
}
