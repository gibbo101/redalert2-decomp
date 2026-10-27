#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/quoted_printable.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);
extern char const unknown_set_campaign_log_007d4ff8[];
// @ref _strncpy=007823d0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_set_campaign_log_007d4ff8@@3QBDB=007d4ff8
bool CoopCampaignClass::Set_Campaign_Info_0048f7d0(UnknownDescriptionList_00490E00 const &campaigns, int index, DynamicVectorClass<int> choices, char const *second_name, char const *first_name)
{
    if(index>=0 && index<campaigns.Count) {
        UnknownDescriptionRecord_00490E00 const *record=&campaigns.Entries[index];
        CurrentMap=-1;
        Kills[0]=0;
        Kills[1]=0;
        Built[0]=0;
        Built[1]=0;
        Lost[0]=0;
        Lost[1]=0;
        Score[0]=0;
        Score[1]=0;
        Time=0;
        if((signed char)record->MapCount!=choices.Count()) return false;
        CampaignType=index;
        Initialized=true;
        if(MapNames) {
            for(int i=0;i<MapCount;++i) {
                if(MapNames[i]) delete [] MapNames[i];
            }
            delete [] MapNames;
        }
        MapNames=0;
        MapCount=0;
        MapNames=new char *[choices.Count()];
        for(int m=0;m<choices.Count();++m) {
            MapNames[m]=new char[260];
            strncpy(MapNames[m],record->Maps+(m*3+choices[m])*260,259);
        }
        MapCount=choices.Count();
        CurrentMap=0;
        if(first_name) strcpy(FirstName,Quoted_Printable_Decode_0048df70(first_name));
        else FirstName[0]=0;
        if(second_name) strcpy(SecondName,Quoted_Printable_Decode_0048df70(second_name));
        else SecondName[0]=0;
        Debug_Printf(unknown_set_campaign_log_007d4ff8,CampaignType);
    }
    return Initialized;
}
