// RulesClass::Wall_Model (0x00647DE0)
// @ref ??_C@_0BH@LBAL@AlliedWallTransparency?$AA@=007eff7c
// @ref ??_C@_0BI@PMKE@WallPenetratorThreshold?$AA@=007eff64
// @ref _RulesSection_WallModel=007a9050
// @ref ??_C@_09JCLC@WallModel?$AA@=007eecac
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"

bool RulesClass::Wall_Model(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_WallModel)) {
        unknown_1498 = ini.Get_Bool(RulesSection_WallModel, "AlliedWallTransparency", unknown_1498);
        WallPenetratorThreshold = ini.Get_Double(RulesSection_WallModel, "WallPenetratorThreshold", WallPenetratorThreshold);
        return true;
    }
    return false;
}
