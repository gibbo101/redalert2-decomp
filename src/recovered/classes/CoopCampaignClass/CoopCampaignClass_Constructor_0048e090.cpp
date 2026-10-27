#include "shared/coop_campaign.hpp"
#include "shared/crt_string.hpp"
char *__fastcall Unknown_006FA120(unsigned short const *string);
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
CoopCampaignClass::CoopCampaignClass(unsigned short const *first, unsigned short const *second)
{
    Set_Names(first,second);
    FirstHouse=-2;
    SecondHouse=-2;
    FirstColor=-2;
    SecondColor=-2;
    MapNames=0;
    CampaignType=-1;
    CurrentMap=-1;
    Initialized=false;
    MapCount=0;
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
