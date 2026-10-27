// RulesClass::Jumpjet_Controls (0x0064D9E0)
// @ref ??_C@_05IJFF@Climb?$AA@=007f1ab4
// @ref ??_C@_05PDDA@Speed?$AA@=007d381c
// @ref ??_C@_08KEIB@TurnRate?$AA@=007f1abc
// @ref ??_C@_0BA@MPHD@WobbleDeviation?$AA@=007f1a80
// @ref ??_C@_0BB@EEKP@WobblesPerSecond?$AA@=007f1a90
// @ref ??_C@_0N@BCHG@Acceleration?$AA@=007d13e0
// @ref ??_C@_0N@OFEE@CruiseHeight?$AA@=007f1aa4
// @ref _RulesSection_JumpjetControls=007a909c
// @ref ??_C@_0BA@GMGL@JumpjetControls?$AA@=007eebac
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"

bool RulesClass::Jumpjet_Controls(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_JumpjetControls)) {
        unknown_368 = ini.Get_Int(RulesSection_JumpjetControls, "TurnRate", unknown_368);
        Speed = ini.Get_Int(RulesSection_JumpjetControls, "Speed", Speed);
        Climb = ini.Get_Double(RulesSection_JumpjetControls, "Climb", Climb);
        unknown_378 = ini.Get_Int(RulesSection_JumpjetControls, "CruiseHeight", unknown_378);
        Acceleration = ini.Get_Double(RulesSection_JumpjetControls, "Acceleration", Acceleration);
        WobblesPerSecond = ini.Get_Double(RulesSection_JumpjetControls, "WobblesPerSecond", WobblesPerSecond);
        WobbleDeviation = ini.Get_Int(RulesSection_JumpjetControls, "WobbleDeviation", WobbleDeviation);
        return true;
    }
    return false;
}
