#define VECTOR_IMPLEMENT_ALL
#define GENERIC_LIST_IMPLEMENT_CONSTRUCTOR
#include "shared/unknown_description_list.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/string_table.hpp"
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);
extern char unknown_campaign_buffer_008519c8[128];
// @ref ?unknown_campaign_buffer_008519c8@@3PADA=008519c8
// @ref ??0GenericList@@QAE@XZ=00490e80
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref _wcscpy=00783689
// @ref _strtok=00782ec2
extern char const unknown_campaign_file_007d514c[];
// @ref ?unknown_campaign_file_007d514c@@3QBDB=007d514c
extern char const unknown_campaigns_key_007d5140[];
// @ref ?unknown_campaigns_key_007d5140@@3QBDB=007d5140
extern char const unknown_map_count_key_007d5128[];
// @ref ?unknown_map_count_key_007d5128@@3QBDB=007d5128
extern char const unknown_campaign_name_key_007d5118[];
// @ref ?unknown_campaign_name_key_007d5118@@3QBDB=007d5118
extern char const unknown_source_file_007d5104[];
// @ref ?unknown_source_file_007d5104@@3QBDB=007d5104
extern char const unknown_campaign_ai_key_007d50f8[];
// @ref ?unknown_campaign_ai_key_007d50f8@@3QBDB=007d50f8
extern char const unknown_campaign_player_key_007d50e8[];
// @ref ?unknown_campaign_player_key_007d50e8@@3QBDB=007d50e8
extern char const unknown_campaign_enemy_key_007d50d8[];
// @ref ?unknown_campaign_enemy_key_007d50d8@@3QBDB=007d50d8
extern char const unknown_map_format_007d4f64[];
// @ref ?unknown_map_format_007d4f64@@3QBDB=007d4f64
extern char const unknown_ai_default_007ceaec[];
// @ref ?unknown_ai_default_007ceaec@@3QBDB=007ceaec
extern char const unknown_token_delimiters_007ce9c0[];
// @ref ?unknown_token_delimiters_007ce9c0@@3QBDB=007ce9c0
UnknownDescriptionList_00490E00::UnknownDescriptionList_00490E00()
{
    CCFileClass file(unknown_campaign_file_007d514c);
    if(!Ini.Load(file,false,false)) {
        Count=0;
        Entries=0;
        Initialized=false;
        return;
    }
    Count=Ini.Entry_Count(unknown_campaigns_key_007d5140);
    if(Count<=0) { Count=0; Entries=0; }
    else {
        Entries=new UnknownDescriptionRecord_00490E00[Count];
        if(Entries) {
            for(int i=0;i<Count;++i) {
                char const *entry=Ini.Get_Entry(unknown_campaigns_key_007d5140,i);
                if(!entry) continue;
                char section[128];
                Ini.Get_String(unknown_campaigns_key_007d5140,entry,0,section,128);
                int map_count=Ini.Get_Int(section,unknown_map_count_key_007d5128,0);
                if(Ini.Get_String(section,unknown_campaign_name_key_007d5118,0,unknown_campaign_buffer_008519c8,128)) {
                    wchar_t const *name=StringTable::Load_String(unknown_campaign_buffer_008519c8,0,unknown_source_file_007d5104,0x408);
                    Entries[i].Name=new wchar_t[129];
                    if(Entries[i].Name) wcscpy(Entries[i].Name,name);
                }
                Ini.Get_String(section,unknown_campaign_ai_key_007d50f8,unknown_ai_default_007ceaec,unknown_campaign_buffer_008519c8,128);
                Entries[i].AIName=new char[strlen(unknown_campaign_buffer_008519c8)+1];
                strcpy(Entries[i].AIName,unknown_campaign_buffer_008519c8);
                Entries[i].Index=i;
                Entries[i].MapCount=(char)map_count;
                Entries[i].Maps=new char[map_count*0x30C];
                if(Ini.Get_String(section,unknown_campaign_player_key_007d50e8,0,unknown_campaign_buffer_008519c8,128)) {
                    char *token=strtok(unknown_campaign_buffer_008519c8,unknown_token_delimiters_007ce9c0);
                    if(token) { char *copy=new char[strlen(token)+1]; strcpy(copy,token); Entries[i].Players.Add(copy); }
                    token=strtok(0,unknown_token_delimiters_007ce9c0);
                    while(token) {
                        char *copy=new char[strlen(token)+1];
                        strcpy(copy,token);
                        Entries[i].Players.Add(copy);
                        token=strtok(0,unknown_token_delimiters_007ce9c0);
                    }
                }
                if(Ini.Get_String(section,unknown_campaign_enemy_key_007d50d8,0,unknown_campaign_buffer_008519c8,128)) {
                    char *token=strtok(unknown_campaign_buffer_008519c8,unknown_token_delimiters_007ce9c0);
                    if(token) { char *copy=new char[strlen(token)+1]; strcpy(copy,token); Entries[i].Enemies.Add(copy); }
                    token=strtok(0,unknown_token_delimiters_007ce9c0);
                    while(token) {
                        char *copy=new char[strlen(token)+1];
                        strcpy(copy,token);
                        Entries[i].Enemies.Add(copy);
                        token=strtok(0,unknown_token_delimiters_007ce9c0);
                    }
                }
                for(int m=1;m<map_count+1;++m) {
                    char key[32];
                    sprintf(key,unknown_map_format_007d4f64,m);
                    if(Ini.Get_String(section,key,0,unknown_campaign_buffer_008519c8,128)) {
                        char *token=strtok(unknown_campaign_buffer_008519c8,unknown_token_delimiters_007ce9c0);
                        if(token) strcpy(Entries[i].Maps+(m-1)*0x30C,token);
                        token=strtok(0,unknown_token_delimiters_007ce9c0);
                        if(token) strcpy(Entries[i].Maps+(m-1)*0x30C+0x104,token);
                        token=strtok(0,unknown_token_delimiters_007ce9c0);
                        if(token) strcpy(Entries[i].Maps+(m-1)*0x30C+0x208,token);
                    }
                }
            }
        }
    }
    Initialized=true;
}

// @ref ??0?$VectorClass@PAD@@QAE@IPBQAD@Z=004913e0
// @ref ??_7?$DynamicVectorClass@PAD@@6B@=0079e55c
