#include "shared/coop_campaign.hpp"
CoopCampaignClass::CoopCampaignClass()
{
    FirstName[0]=0;
    SecondName[0]=0;
    FirstHouse=-2;
    SecondHouse=-2;
    FirstColor=-2;
    SecondColor=-2;

    MapNames=0;
    CampaignType=-1;
    Initialized=false;
    MapCount=0;
    CurrentMap=-1;
    Kills[0]=0;
    Kills[1]=0;
    Built[0]=0;
    Built[1]=0;
    Lost[0]=0;
    Lost[1]=0;
    Time=0;
    Score[0]=0;
    Score[1]=0;
}
