#include "shared/coop_campaign.hpp"
bool CoopCampaignClass::Get_Second_Player_Settings_0048fbc0(int *house,int *color)
{
    if(Initialized) {
        *house=SecondHouse;
        *color=SecondColor;
        return true;
    }
    return false;
}
