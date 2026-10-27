#define DESCRIPTION_LIST_INLINE_GET_RECORD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
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
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
extern int unknown_player_slot_types_00a3d300[];
void Prepare_Campaign_Save_File(FileClass &file);
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUUnknownPlayerEntry@@@@A=00a3fa7c
// @ref ?unknown_player_slot_types_00a3d300@@3PAHA=00a3d300
// @ref ?unknown_66e290@UnknownPlayerEntry@@QAEHXZ=0066e290
// @ref ?Get_Color_0066e2a0@UnknownPlayerEntry@@QAEHXZ=0066e2a0
// @ref ?Put_HousesType@CCINIClass@@QAE_NPBD0H@Z=0046aab0
// @ref ?Put_Int@INIClass@@QAE_NPBD0HH@Z=0050d6e0
// @ref ?Put_String@INIClass@@QAE_NPBD00@Z=0050e5f0
bool CoopCampaignClass::Save_Campaign_0048f040()
{
    if(Initialized && FirstName[0] && SecondName[0]) {
    UnknownDescriptionList_00490E00 *campaigns=new UnknownDescriptionList_00490E00;
    UnknownDescriptionRecord_00490E00 *record;
    if(!campaigns->Get_Record_00490C50(CampaignType,&record)) {
        delete campaigns;
        return false;
    }
    {
        CCFileClass saved(campaign_save_filename_007d4f48);
        CCINIClass ini;
        ini.Load(saved,false,false);
        saved.Close();
        char section[100];
        strcpy(section,Quoted_Printable_Encode_0048dec0(FirstName));
        strcat(section,Quoted_Printable_Encode_0048dec0(SecondName));
        CCFileClass output;
        Prepare_Campaign_Save_File(output);
        ini.Clear(section,0);
        ini.Put_Int(section,campaign_key_CurrentMap_007d4fec,CurrentMap);
        ini.Put_Int(section,campaign_key_CampaignType_007d4fd4,CampaignType);
        for(int i=0;i<(signed char)record->MapCount;++i) {
            char key[32];
            sprintf(key,campaign_key_Map_format_007d4f64,i+1);
            ini.Put_String(section,key,MapNames[i]);
        }
        if(unknown_players_a3fa7c.Count()) {
            ini.Put_HousesType(section,campaign_key_House1_007d4fcc,unknown_players_a3fa7c[0]->unknown_66e290());
            ini.Put_Int(section,campaign_key_Color1_007d4fc4,unknown_players_a3fa7c[0]->Get_Color_0066e2a0());
        }
        for(int player=1;player<unknown_players_a3fa7c.Count();++player) {
            if(unknown_player_slot_types_00a3d300[player-1]==-1) {
                ini.Put_HousesType(section,campaign_key_House2_007d4fbc,unknown_players_a3fa7c[player]->unknown_66e290());
                ini.Put_Int(section,campaign_key_Color2_007d4fb4,unknown_players_a3fa7c[player]->Get_Color_0066e2a0());
                break;
            }
        }
        ini.Put_Int(section,campaign_key_Time_007d4f6c,Time);
        ini.Put_Int(section,campaign_key_Kills1_007d4fac,Kills[0]);
        ini.Put_Int(section,campaign_key_Kills2_007d4fa4,Kills[1]);
        ini.Put_Int(section,campaign_key_Built1_007d4f9c,Built[0]);
        ini.Put_Int(section,campaign_key_Built2_007d4f94,Built[1]);
        ini.Put_Int(section,campaign_key_Lost1_007d4f8c,Lost[0]);
        ini.Put_Int(section,campaign_key_Lost2_007d4f84,Lost[1]);
        ini.Put_Int(section,campaign_key_Score1_007d4f7c,Score[0]);
        ini.Put_Int(section,campaign_key_Score2_007d4f74,Score[1]);
        ini.Save(output,false);
        output.Close();
    }
    delete campaigns;
    Initialized=true;
    return true;
    }
    return false;
}
