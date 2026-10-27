// RulesClass::Radiation (0x00647B60)
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_08LCBP@RadColor?$AA@=007efe94
// @ref ??_C@_0BE@IHO@RadDurationMultiple?$AA@=007eff10
// @ref ??_C@_0BE@JPAH@RadApplicationDelay?$AA@=007efefc
// @ref ??_C@_0M@PJCI@RadLevelMax?$AA@=007efef0
// @ref ??_C@_0O@FFPL@RadLevelDelay?$AA@=007efee0
// @ref ??_C@_0O@JDDA@RadLightDelay?$AA@=007efed0
// @ref ??_C@_0O@NJDI@RadTintFactor?$AA@=007efea0
// @ref ??_C@_0P@GJKA@RadLevelFactor?$AA@=007efec0
// @ref ??_C@_0P@HKGG@RadLightFactor?$AA@=007efeb0
// @ref ??_C@_0P@OFBG@RadSiteWarhead?$AA@=007efe84
// @ref _RulesSection_Radiation=007a9048
// @ref ??_C@_09DMND@Radiation?$AA@=007eecc8
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/warhead_type.hpp"

bool RulesClass::Radiation(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_Radiation)) {
        RadDurationMultiple = ini.Get_Int(RulesSection_Radiation, "RadDurationMultiple", RadDurationMultiple);
        unknown_144c = ini.Get_Int(RulesSection_Radiation, "RadApplicationDelay", unknown_144c);
        RadLevelMax = ini.Get_Int(RulesSection_Radiation, "RadLevelMax", RadLevelMax);
        RadLevelDelay = ini.Get_Int(RulesSection_Radiation, "RadLevelDelay", RadLevelDelay);
        RadLightDelay = ini.Get_Int(RulesSection_Radiation, "RadLightDelay", RadLightDelay);
        unknown_1460 = ini.Get_Double(RulesSection_Radiation, "RadLevelFactor", unknown_1460);
        RadLightFactor = ini.Get_Double(RulesSection_Radiation, "RadLightFactor", RadLightFactor);
        RadTintFactor = ini.Get_Double(RulesSection_Radiation, "RadTintFactor", RadTintFactor);
        RadColor = ini.Get_RGB(RulesSection_Radiation, "RadColor", RadColor);
        unknown_147c = Get_Type(ini, RulesSection_Radiation, "RadSiteWarhead", unknown_147c);
        return true;
    }
    return false;
}
