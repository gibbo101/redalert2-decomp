#include "shared/coop_campaign.hpp"
bool CoopCampaignClass::Get_Campaign_Type_0048e6b0(int *value)
{
    if(!Initialized) return false;
    *value=CampaignType;
    return true;
}
