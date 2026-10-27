// RulesClass::IQ (0x0064D850)
// @ref ??_C@_07FINC@Scatter?$AA@=007e1d3c
// @ref ??_C@_08IKIM@SellBack?$AA@=007f1a1c
// @ref ??_C@_08KGJO@Aircraft?$AA@=007cdeb8
// @ref ??_C@_09BNDL@GuardArea?$AA@=007d1dd0
// @ref ??_C@_09IBOJ@Harvester?$AA@=007f1a28
// @ref ??_C@_0L@FHGC@RepairSell?$AA@=007f1a4c
// @ref ??_C@_0L@GJDK@Production?$AA@=007f1a58
// @ref ??_C@_0M@JLKN@MaxIQLevels?$AA@=007f1a74
// @ref ??_C@_0M@KHHB@ContentScan?$AA@=007f1a34
// @ref ??_C@_0N@JJPO@SuperWeapons?$AA@=007f1a64
// @ref _RulesSection_IQ=007a9098
// @ref ??_C@_02KPHM@IQ?$AA@=007da854
// @ref ??_C@_09HAOM@AutoCrush?$AA@=007f1a40
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"

bool RulesClass::IQ(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_IQ)) {
        MaxIQ = ini.Get_Int(RulesSection_IQ, "MaxIQLevels", MaxIQ);
        IQSuperWeapons = ini.Get_Int(RulesSection_IQ, "SuperWeapons", IQSuperWeapons);
        IQProduction = ini.Get_Int(RulesSection_IQ, "Production", IQProduction);
        unknown_10a8 = ini.Get_Int(RulesSection_IQ, "GuardArea", unknown_10a8);
        IQRepairSell = ini.Get_Int(RulesSection_IQ, "RepairSell", IQRepairSell);
        unknown_10b0 = ini.Get_Int(RulesSection_IQ, "AutoCrush", unknown_10b0);
        IQScatter = ini.Get_Int(RulesSection_IQ, "Scatter", IQScatter);
        unknown_10b8 = ini.Get_Int(RulesSection_IQ, "ContentScan", unknown_10b8);
        IQAircraft = ini.Get_Int(RulesSection_IQ, "Aircraft", IQAircraft);
        IQHarvester = ini.Get_Int(RulesSection_IQ, "Harvester", IQHarvester);
        IQSellBack = ini.Get_Int(RulesSection_IQ, "SellBack", IQSellBack);
        return true;
    }
    return false;
}
