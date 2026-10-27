#include "shared/coop_campaign.hpp"
bool CoopCampaignClass::Get_First_Player_Settings_0048fb90(int *house,int *color)
{
    if(Initialized) {
        *house=FirstHouse;
        *color=FirstColor;
        return true;
    }
    return false;
}
