// static int __fastcall CampaignClass::Find_Index(char const *name) (0x00465580)
// The index in Campaigns of the campaign with this ID (case-insensitive), or -1.
#include "shared/campaign.hpp"

int __fastcall CampaignClass::Find_Index(char const *name)
{
    for (int index = 0; index < Campaigns.Count(); index++) {
        CampaignClass *campaign = Campaigns[index];
        if (_stricmp(campaign->ID, name) == 0) {
            return index;
        }
    }
    return -1;
}
