#define LIST_DECLARE_CONSTRUCTOR
#define INDEX_DECLARE_CONSTRUCTOR
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/quoted_printable.hpp"
extern char const campaign_save_filename_007d4f48[];
char *__fastcall Quoted_Printable_Encode_0048dec0(char const *input);
// @ref ?campaign_save_filename_007d4f48@@3QBDB=007d4f48
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Load@CCINIClass@@QAEHAAVFileClass@@_N1@Z=004696b0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0
// @ref ?Get_HousesType@CCINIClass@@QBEHPBD0H@Z=0046aa00
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ??0UnknownDescriptionList_00490E00@@QAE@XZ=00490510
// @ref ??1UnknownDescriptionList_00490E00@@QAE@XZ=00490ca0
// @ref _sprintf=007820f4
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
bool CoopCampaignClass::Load_Saved_Campaign_0048eb30()
{
    if(!FirstName[0] || !SecondName[0]) return false;
    char section[100];
    strcpy(section,Quoted_Printable_Encode_0048dec0(FirstName));
    strcat(section,Quoted_Printable_Encode_0048dec0(SecondName));
    CCFileClass saved(campaign_save_filename_007d4f48);
    CCINIClass ini;
    if(!ini.Load(saved,false,false)) return false;
    CurrentMap=ini.Get_Int(section,campaign_key_CurrentMap_007d4fec,0);
    ini.Get_Int(section,campaign_key_Score_007d4fe4,0);
    CampaignType=ini.Get_Int(section,campaign_key_CampaignType_007d4fd4,-1);
    FirstHouse=ini.Get_HousesType(section,campaign_key_House1_007d4fcc,-2);
    FirstColor=ini.Get_Int(section,campaign_key_Color1_007d4fc4,-2);
    SecondHouse=ini.Get_HousesType(section,campaign_key_House2_007d4fbc,-2);
    SecondColor=ini.Get_Int(section,campaign_key_Color2_007d4fb4,-2);
    Kills[0]=ini.Get_Int(section,campaign_key_Kills1_007d4fac,0);
    Kills[1]=ini.Get_Int(section,campaign_key_Kills2_007d4fa4,0);
    Built[0]=ini.Get_Int(section,campaign_key_Built1_007d4f9c,0);
    Built[1]=ini.Get_Int(section,campaign_key_Built2_007d4f94,0);
    Lost[0]=ini.Get_Int(section,campaign_key_Lost1_007d4f8c,0);
    Lost[1]=ini.Get_Int(section,campaign_key_Lost2_007d4f84,0);
    Score[0]=ini.Get_Int(section,campaign_key_Score1_007d4f7c,0);
    Score[1]=ini.Get_Int(section,campaign_key_Score2_007d4f74,0);
    Time=ini.Get_Int(section,campaign_key_Time_007d4f6c,0);
    UnknownDescriptionList_00490E00 *campaigns=new UnknownDescriptionList_00490E00;
    if(CampaignType>=0 && CampaignType<campaigns->Count) {
        UnknownDescriptionRecord_00490E00 const &record=campaigns->Entries[CampaignType];
        MapCount=(signed char)record.MapCount;
        MapNames=new char *[(signed char)record.MapCount];
        for(int i=0;i<MapCount;++i) {
            char key[32];
            sprintf(key,campaign_key_Map_format_007d4f64,i+1);
            MapNames[i]=new char[260];
            ini.Get_String(section,key,campaign_key_Map_default_007d4f58,MapNames[i],260);
        }
        delete campaigns;
        Initialized=true;
        return true;
    }
    MapCount=0;
    delete campaigns;
    return false;
}
