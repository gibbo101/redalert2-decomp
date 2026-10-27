#include "shared/coop_campaign.hpp"
bool CoopCampaignClass::Get_Current_Map_0048e6f0(int *value)
{
    if(!Initialized) return false;
    *value=CurrentMap;
    return true;
}
