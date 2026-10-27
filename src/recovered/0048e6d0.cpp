#include "shared/coop_campaign.hpp"
bool CoopCampaignClass::Get_Map_Count_0048e6d0(int *value)
{
    if(!Initialized) return false;
    *value=MapCount;
    return true;
}
