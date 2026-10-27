// RulesClass::Elevation_Model (0x00647D40)
// @ref ??_C@_0BC@KJGN@ElevationBonusCap?$AA@=007eff24
// @ref ??_C@_0BD@IHPA@ElevationIncrement?$AA@=007eff50
// @ref ??_C@_0BI@NMLO@ElevationIncrementBonus?$AA@=007eff38
// @ref _RulesSection_ElevationModel=007a904c
// @ref ??_C@_0P@LGMK@ElevationModel?$AA@=007eecb8
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"

bool RulesClass::Elevation_Model(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_ElevationModel)) {
        unknown_1480 = ini.Get_Int(RulesSection_ElevationModel, "ElevationIncrement", unknown_1480);
        unknown_1488 = ini.Get_Double(RulesSection_ElevationModel, "ElevationIncrementBonus", unknown_1488);
        unknown_1490 = ini.Get_Double(RulesSection_ElevationModel, "ElevationBonusCap", unknown_1490);
        return true;
    }
    return false;
}
