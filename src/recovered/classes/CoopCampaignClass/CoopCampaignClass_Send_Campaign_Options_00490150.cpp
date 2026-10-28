#define DESCRIPTION_LIST_INLINE_GET_RECORD
#define LIST_DECLARE_CONSTRUCTOR
#define INDEX_DECLARE_CONSTRUCTOR
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/quoted_printable.hpp"
#include "shared/debug_printf.hpp"
#include "shared/lobby.hpp"
extern "C" int __cdecl _stricmp(char const *first,char const *second);
char *__fastcall Quoted_Printable_Encode_0048dec0(char const *input);
extern char const campaign_options_format_007d5068[];
extern char const campaign_options_separator_007d5060[];
extern char const campaign_options_comma_007ce9c0[];
extern char const campaign_map_choice_format_007cfa6c[];
extern char const campaign_sending_log_007d5030[];
extern char const campaign_sent_log_007d5024[];
// @ref _sprintf=007820f4
// @ref __stricmp=00781f20
// @ref ?Send_Game_Options_005c3c60@@YIXPBD@Z=005c3c60
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?campaign_options_format_007d5068@@3QBDB=007d5068
// @ref ?campaign_options_separator_007d5060@@3QBDB=007d5060
// @ref ?campaign_options_comma_007ce9c0@@3QBDB=007ce9c0
// @ref ?campaign_map_choice_format_007cfa6c@@3QBDB=007cfa6c
// @ref ?campaign_sending_log_007d5030@@3QBDB=007d5030
// @ref ?campaign_sent_log_007d5024@@3QBDB=007d5024
bool CoopCampaignClass::Send_Campaign_Options_00490150(UnknownDescriptionList_00490E00 &campaigns)
{
    if(!Initialized) return false;
    UnknownDescriptionRecord_00490E00 *record;
    if(!campaigns.Get_Record_00490C50(CampaignType,&record)) return false;
    char message[400];
    sprintf(message,campaign_options_format_007d5068,CampaignType,CurrentMap,Time,
            Kills[0],Built[0],Lost[0],Score[0],Kills[1],Built[1],Lost[1],Score[1]);
    for(int map=0;map<MapCount;++map) {
        int choice=0;
        for(int option=0;option<3;++option) {
            if(_stricmp(record->Maps+map*0x30c+option*260,MapNames[map])==0) {
                choice=option;
                break;
            }
        }
        char choice_text[16];
        sprintf(choice_text,campaign_map_choice_format_007cfa6c,choice);
        strcat(message,choice_text);
    }
    strcat(message,campaign_options_separator_007d5060);
    strcat(message,Quoted_Printable_Encode_0048dec0(FirstName));
    strcat(message,campaign_options_comma_007ce9c0);
    strcat(message,Quoted_Printable_Encode_0048dec0(SecondName));
    Debug_Printf(campaign_sending_log_007d5030,message);
    Send_Game_Options_005c3c60(message);
    Debug_Printf(campaign_sent_log_007d5024);
    return true;
}
