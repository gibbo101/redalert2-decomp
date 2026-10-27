#include "shared/coop_campaign.hpp"
bool CoopCampaignClass::Get_Map_Name_0048fb40(char **name,int index)
{
    bool result=false;
    *name=0;
    if(index==-1) index=CurrentMap;
    if(index<0 || index>=MapCount) index=-1;
    if(Initialized) {
        if(index!=-1) *name=MapNames[index];
        if(*name!=0) result=true;
    }
    return result;
}
