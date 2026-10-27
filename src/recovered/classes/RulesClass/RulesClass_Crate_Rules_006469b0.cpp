// RulesClass::Crate_Rules (0x006469B0)
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_07OBAC@FreeMCV?$AA@=007efa7c
// @ref ??_C@_08PLFK@CrateImg?$AA@=007efa60
// @ref ??_C@_09CLKA@WoodCrate?$AA@=007ef9d0
// @ref ??_C@_0L@HFPJ@CrateRegen?$AA@=007efa08
// @ref ??_C@_0L@HNME@WaterCrate?$AA@=007ef9c4
// @ref ??_C@_0M@DBC@CrateRadius?$AA@=007efa14
// @ref ??_C@_0M@FKNO@SilverCrate?$AA@=007ef9dc
// @ref ??_C@_0N@BAIF@CrateMaximum?$AA@=007efa20
// @ref ??_C@_0N@GGLF@WoodCrateImg?$AA@=007efa6c
// @ref ??_C@_0N@HPAO@CrateMinimum?$AA@=007efa30
// @ref ??_C@_0O@CENP@UnitCrateType?$AA@=007ef9f8
// @ref ??_C@_0O@JJCA@WaterCrateImg?$AA@=007efa50
// @ref ??_C@_0P@GNAO@HealCrateSound?$AA@=007efa40
// @ref ??_C@_0P@NOLM@SoloCrateMoney?$AA@=007ef9e8
// @ref ?Find_Or_Make@OverlayTypeClass@@SIPAV1@PBD@Z=005dcf70
// @ref _RulesSection_CrateRules=007a9040
// @ref ??_C@_0L@LLFF@CrateRules?$AA@=007eece4
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/overlay_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/voc_class.hpp"

bool RulesClass::Crate_Rules(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_CrateRules)) {
        FreeMCV = ini.Get_Bool(RulesSection_CrateRules, "FreeMCV", FreeMCV);
        unknown_f0 = Get_Type(ini, RulesSection_CrateRules, "WoodCrateImg", unknown_f0);
        unknown_f4 = Get_Type(ini, RulesSection_CrateRules, "CrateImg", unknown_f4);
        unknown_f8 = Get_Type(ini, RulesSection_CrateRules, "WaterCrateImg", unknown_f8);
        HealCrateSound = Get_Sound(ini, RulesSection_CrateRules, "HealCrateSound", HealCrateSound);
        CrateMinimum = ini.Get_Int(RulesSection_CrateRules, "CrateMinimum", CrateMinimum);
        CrateMaximum = ini.Get_Int(RulesSection_CrateRules, "CrateMaximum", CrateMaximum);
        CrateRadius = ini.Get_Lepton(RulesSection_CrateRules, "CrateRadius", CrateRadius);
        CrateRegen = ini.Get_Double(RulesSection_CrateRules, "CrateRegen", CrateRegen);
        UnitCrateType = Get_Type(ini, RulesSection_CrateRules, "UnitCrateType", UnitCrateType);
        SoloCrateMoney = ini.Get_Int(RulesSection_CrateRules, "SoloCrateMoney", SoloCrateMoney);
        SilverCrate = ini.Get_CrateType(RulesSection_CrateRules, "SilverCrate", SilverCrate);
        WoodCrate = ini.Get_CrateType(RulesSection_CrateRules, "WoodCrate", WoodCrate);
        WaterCrate = ini.Get_CrateType(RulesSection_CrateRules, "WaterCrate", WaterCrate);
        return true;
    }
    return false;
}
