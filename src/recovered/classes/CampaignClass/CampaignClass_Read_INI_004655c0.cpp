// bool CampaignClass::Read_INI(CCINIClass &ini) (0x004655C0, slot 25)
// @ref ?Get_Wide_String@CampaignINI@@QBEHPBD0PAGH@Z=0050f010
// @ref ??_C@_02JOMG@CD?$AA@=007d1474
// @ref ??_C@_08DFKC@Scenario?$AA@=007d145c
// @ref ??_C@_09PAHE@DebugOnly?$AA@=007d1450
// @ref ??_C@_0BF@COOB@?5?9?5for?5debug?1testing?$AA@=007d142c
// @ref ??_C@_0L@HNJO@FinalMovie?$AA@=007d1468
// @ref ??_C@_0M@DKEL@Description?$AA@=007d1444
// The campaign's CD, final movie and scenario (upper case), and its
// description; debug-only campaigns get " - for debug/testing" appended.
#include "shared/campaign.hpp"

bool CampaignClass::Read_INI(CCINIClass &ini)
{
    if (AbstractTypeClass::Read_INI(ini)) {
        unknown_98 = ini.Get_Int(ID, "CD", unknown_98);
        unknown_29c = ini.Get_Listed_Name(ID, "FinalMovie", unknown_29c);
        ini.Get_String(ID, "Scenario", Scenario, Scenario, sizeof(Scenario));
        _strupr(Scenario);
        if (!ini.Get_Bool(ID, "DebugOnly", false)) {
            ((CampaignINI &)ini).Get_Wide_String(ID, "Description", Description, sizeof(Description) / sizeof(Description[0]));
        } else {
            char buffer[1024];
            ini.Get_String(ID, "Description", 0, buffer, sizeof(buffer));
            strcat(buffer, " - for debug/testing");
            Unknown_006FA0C0(Description, buffer, -1);
        }
        return true;
    }
    return false;
}
