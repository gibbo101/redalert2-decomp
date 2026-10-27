#define LIST_DECLARE_CONSTRUCTOR
#define INDEX_DECLARE_CONSTRUCTOR
#include "shared/coop_campaign.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/quoted_printable.hpp"
extern char const campaign_save_filename_007d4f48[];
char *__fastcall Quoted_Printable_Encode_0048dec0(char const *input);
// @ref ?campaign_save_filename_007d4f48@@3QBDB=007d4f48
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Load@CCINIClass@@QAEHAAVFileClass@@_N1@Z=004696b0
// @ref ?Close@CCFileClass@@UAEXXZ=004691f0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??_7CCINIClass@@6B@=0079aae4
extern char const campaign_key_CurrentMap_007d4fec[];
// @ref ?campaign_key_CurrentMap_007d4fec@@3QBDB=007d4fec
extern char const campaign_key_Score_007d4fe4[];
// @ref ?campaign_key_Score_007d4fe4@@3QBDB=007d4fe4
extern char const campaign_key_CampaignType_007d4fd4[];
// @ref ?campaign_key_CampaignType_007d4fd4@@3QBDB=007d4fd4
extern char const campaign_key_House1_007d4fcc[];
// @ref ?campaign_key_House1_007d4fcc@@3QBDB=007d4fcc
extern char const campaign_key_Color1_007d4fc4[];
// @ref ?campaign_key_Color1_007d4fc4@@3QBDB=007d4fc4
extern char const campaign_key_House2_007d4fbc[];
// @ref ?campaign_key_House2_007d4fbc@@3QBDB=007d4fbc
extern char const campaign_key_Color2_007d4fb4[];
// @ref ?campaign_key_Color2_007d4fb4@@3QBDB=007d4fb4
extern char const campaign_key_Kills1_007d4fac[];
// @ref ?campaign_key_Kills1_007d4fac@@3QBDB=007d4fac
extern char const campaign_key_Kills2_007d4fa4[];
// @ref ?campaign_key_Kills2_007d4fa4@@3QBDB=007d4fa4
extern char const campaign_key_Built1_007d4f9c[];
// @ref ?campaign_key_Built1_007d4f9c@@3QBDB=007d4f9c
extern char const campaign_key_Built2_007d4f94[];
// @ref ?campaign_key_Built2_007d4f94@@3QBDB=007d4f94
extern char const campaign_key_Lost1_007d4f8c[];
// @ref ?campaign_key_Lost1_007d4f8c@@3QBDB=007d4f8c
extern char const campaign_key_Lost2_007d4f84[];
// @ref ?campaign_key_Lost2_007d4f84@@3QBDB=007d4f84
extern char const campaign_key_Score1_007d4f7c[];
// @ref ?campaign_key_Score1_007d4f7c@@3QBDB=007d4f7c
extern char const campaign_key_Score2_007d4f74[];
// @ref ?campaign_key_Score2_007d4f74@@3QBDB=007d4f74
extern char const campaign_key_Time_007d4f6c[];
// @ref ?campaign_key_Time_007d4f6c@@3QBDB=007d4f6c
extern char const campaign_key_Map_format_007d4f64[];
// @ref ?campaign_key_Map_format_007d4f64@@3QBDB=007d4f64
extern char const campaign_key_Map_default_007d4f58[];
// @ref ?campaign_key_Map_default_007d4f58@@3QBDB=007d4f58
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref _sprintf=007820f4
bool CoopCampaignClass::Saved_Map_Is_Undefined_0048fe70(char *map)
{
    if(FirstName[0] && SecondName[0]) {
    CCFileClass saved(campaign_save_filename_007d4f48);
    CCINIClass ini;
    if(!ini.Load(saved,false,false)) {
        saved.Close();
    } else {
    saved.Close();
    char section[100];
    strcpy(section,Quoted_Printable_Encode_0048dec0(FirstName));
    strcat(section,Quoted_Printable_Encode_0048dec0(SecondName));
    int current=ini.Get_Int(section,campaign_key_CurrentMap_007d4fec,0);
    char key[32];
    sprintf(key,campaign_key_Map_format_007d4f64,current+1);
    ini.Get_String(section,key,campaign_key_Map_default_007d4f58,map,260);
    if(strcmp(map,campaign_key_Map_default_007d4f58)==0) return true;
    goto map_is_defined;
    }
    }
map_is_defined:
    return false;
}
