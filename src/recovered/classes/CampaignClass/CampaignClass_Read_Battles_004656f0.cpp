// static void __fastcall CampaignClass::Read_Battles(CCINIClass &ini) (0x004656F0)
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_07INPA@Battles?$AA@=007d1478
// Every [Battles] entry names a campaign: an existing one is found by ID,
// otherwise a new one is made; each then reads its own section.
#include "shared/campaign.hpp"

void __fastcall CampaignClass::Read_Battles(CCINIClass &ini)
{
    int count = ini.Entry_Count("Battles");
    for (int index = 0; index < count; index++) {
        char name[32];
        ini.Get_String("Battles", ini.Get_Entry("Battles", index), "", name, sizeof(name));
        int found = Find_Index(name);
        CampaignClass *campaign;
        if (found == -1) {
            campaign = new CampaignClass(name);
        } else {
            campaign = Campaigns[found];
        }
        campaign->Read_INI(ini);
    }
}
