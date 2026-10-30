#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/rules.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl _strnicmp(char const *,char const *,unsigned int);
extern "C" long __cdecl atol(char const *);
extern "C" long __cdecl time(long *);
int unknown_scheme_index_4cefc0();
WideString __fastcall unknown_number_text_7710c0(int value);
extern char wol_find_requested_name_b29cd8[];
extern char wol_lobby_prefix_7fd358[];
extern char wol_lobby_prefix_7fd360[];
extern char wol_lobby_prefix_7fd368[];
extern char wol_find_string_format_7e7f2c[];
extern char wol_find_numbered_format_7fe1c0[];
extern char wol_find_ok_label_7fe1b4[];
extern char wol_find_none_label_7fe1a4[];
extern char wol_find_gone_label_7fe194[];
extern char wol_find_disabled_label_7fe180[];
extern char wol_find_failed_label_7fe170[];
extern char wol_user_found_label_7fe160[];
extern char wol_user_nochannel_label_7fe148[];
extern char wol_user_disabled_label_7fe130[];
extern char wol_user_offline_label_7fe11c[];
extern char wol_source_file_007fd62c[];
extern unsigned short wol_find_space_7d64f4[];
// @ref __strnicmp=007858d0
// @ref _atol=00782d72
// @ref ?wol_find_requested_name_b29cd8@@3PADA=00b29cd8
// @ref ?wol_lobby_prefix_7fd358@@3PADA=007fd358
// @ref ?wol_lobby_prefix_7fd360@@3PADA=007fd360
// @ref ?wol_lobby_prefix_7fd368@@3PADA=007fd368
// @ref ?wol_find_string_format_7e7f2c@@3PADA=007e7f2c
// @ref ?wol_find_numbered_format_7fe1c0@@3PADA=007fe1c0
// @ref ?wol_find_ok_label_7fe1b4@@3PADA=007fe1b4
// @ref ?wol_find_none_label_7fe1a4@@3PADA=007fe1a4
// @ref ?wol_find_gone_label_7fe194@@3PADA=007fe194
// @ref ?wol_find_disabled_label_7fe180@@3PADA=007fe180
// @ref ?wol_find_failed_label_7fe170@@3PADA=007fe170
// @ref ?wol_user_found_label_7fe160@@3PADA=007fe160
// @ref ?wol_user_nochannel_label_7fe148@@3PADA=007fe148
// @ref ?wol_user_disabled_label_7fe130@@3PADA=007fe130
// @ref ?wol_user_offline_label_7fe11c@@3PADA=007fe11c
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_find_space_7d64f4@@3PAGA=007d64f4
// @ref ?unknown_number_text_7710c0@@YI?AVWideString@@H@Z=007710c0
HRESULT __stdcall CChatEventSink::OnFind(HRESULT result,WOL::Channel *channel)
{
    unsigned int status=0;
    if(unknown_wstring_b26944.Length()!=0) {
        unsigned int *previous=0;
        unknown_names_b29848.Get_Pointer(unknown_wstring_b26944,&previous);
        if(previous) status=*previous;
        char name[64];
        name[0]=0;
        WOL::User user;
        if(channel) {
            if(channel->unknown_00==0) {
                if(!_strnicmp(channel->name,wol_lobby_prefix_7fd360,strlen(wol_lobby_prefix_7fd360))) status=7;
                else if(!_strnicmp(channel->name,wol_lobby_prefix_7fd368,strlen(wol_lobby_prefix_7fd368))) status=8;
                else status=4;
            } else {
                status=5;
                Wstring lookup_name(channel->name);
                WOL::Channel game;
                if(unknown_games_b29990.Find_Name(lookup_name,game)) {
                    if(Unknown_0073c400(&game)) status=8;
                    else if(Unknown_0073c3e0(&game)) status=7;
                }
            }
            if(unknown_wstring_b26944.Length()>0) unknown_channels_b29478.Add(unknown_wstring_b26944,*channel);
            strcpy(name,channel->name);
            if(!strncmp(name,wol_lobby_prefix_7fd358,7)) {
                int value=atol(name+strlen(wol_lobby_prefix_7fd358));
                int division=value/8;
                int remainder=value%8;
                if(division==0) sprintf(name,wol_find_string_format_7e7f2c,unknown_lobby_names_b26c94[remainder]);
                else sprintf(name,wol_find_numbered_format_7fe1c0,unknown_lobby_names_b26c94[remainder],division+1);
            }
            Unknown_005c2d10(unknown_color_7a7360,StringTable::Load_String(wol_find_ok_label_7fe1b4,0,wol_source_file_007fd62c,0x1bae),name);
        } else {
            if(unknown_wstring_b26944.Length()>0) unknown_channels_b29478.Remove_Channel(unknown_wstring_b26944);
            if(result==0x40131) {
                status=3;
                Unknown_005c2d10(unknown_color_7a7360,StringTable::Load_String(wol_find_none_label_7fe1a4,0,wol_source_file_007fd62c,0x1bb7));
            } else if(result==0x40130) {
                status=2;
                Unknown_005c2d10(unknown_color_7a7360,StringTable::Load_String(wol_find_gone_label_7fe194,0,wol_source_file_007fd62c,0x1bbb));
            } else if(result==0x40132) {
                status=1;
                Unknown_005c2d10(unknown_color_7a7360,StringTable::Load_String(wol_find_disabled_label_7fe180,0,wol_source_file_007fd62c,0x1bbf));
            } else {
                Unknown_005c2d10(unknown_color_7a7360,StringTable::Load_String(wol_find_failed_label_7fe170,0,wol_source_file_007fd62c,0x1bc2));
            }
        }
        if(unknown_wstring_b26944.Length()>0) {
            unknown_names_b29848.Add(unknown_wstring_b26944,status);
            unknown_wstring_b26944.Release();
            HWND dialog=Find_Dialog_00735940(0x116);
            if(dialog) Unknown_00755180(dialog);
        }
        if(unknown_wstring_b26944.Length()>0) {
            if((unsigned long)(time(0)-unknown_b2a7f8)<5) return 0;
            unknown_wstring_b26944.Release();
        }
        if(unknown_strings_b29838.Count!=0) {
            if(unknown_strings_b29838.Count>0) {
                unknown_strings_b29838.Get(unknown_wstring_b26944,0);
                unknown_strings_b29838.Remove_Inline(0);
            }
            unknown_b2a7f8=time(0);
            memset(&user,0,sizeof(user));
            strcpy(user.name,unknown_wstring_b26944.Get());
            unknown_chat_a72cfc->unknown_slot24(&user);
        }
        return 0;
    }
    else {
    wchar_t text[128];
    if(channel) {
        if(channel->unknown_00==0 && !strncmp(channel->name,wol_lobby_prefix_7fd358,strlen(wol_lobby_prefix_7fd358))) {
            int value=atol(channel->name+strlen(wol_lobby_prefix_7fd358));
            int division=value/8;
            int remainder=value%8;
            WideString lobby((wchar_t const *)unknown_lobby_names_b26c94[remainder]);
            if(division!=0) {
                lobby+=wol_find_space_7d64f4;
                lobby+=unknown_number_text_7710c0(division+1);
            }
            wchar_t const *user_name=Unknown_006FA180(wol_find_requested_name_b29cd8);
            wchar_t const *lobby_name=lobby.Get();
            swprintf(text,StringTable::Load_String(wol_user_found_label_7fe160,0,wol_source_file_007fd62c,0x1b5b),user_name,lobby_name);
        } else {
            wchar_t const *user_name=Unknown_006FA180(wol_find_requested_name_b29cd8);
            wchar_t const *channel_name=Unknown_006FA180(channel->name);
            swprintf(text,StringTable::Load_String(wol_user_found_label_7fe160,0,wol_source_file_007fd62c,0x1b5d),user_name,channel_name);
        }
    } else if(result==0x40130) {
        swprintf(text,StringTable::Load_String(wol_user_offline_label_7fe11c,0,wol_source_file_007fd62c,0x1b64),Unknown_006FA180(wol_find_requested_name_b29cd8));
    } else if(result==0x40131) {
        swprintf(text,StringTable::Load_String(wol_user_nochannel_label_7fe148,0,wol_source_file_007fd62c,0x1b66),Unknown_006FA180(wol_find_requested_name_b29cd8));
    } else if(result==0x40132) {
        swprintf(text,StringTable::Load_String(wol_user_disabled_label_7fe130,0,wol_source_file_007fd62c,0x1b68),Unknown_006FA180(wol_find_requested_name_b29cd8));
    } else {
        swprintf(text,StringTable::Load_String(wol_user_offline_label_7fe11c,0,wol_source_file_007fd62c,0x1b6a),Unknown_006FA180(wol_find_requested_name_b29cd8));
    }
    HWND dialog=Unknown_00735B10();
    if(dialog) {
        if(GetDlgItem(dialog,0x53f)) {
            Unknown_005C2C80(unknown_color_7a7360,text);
            return 0;
        }
        if(GetDlgItem(dialog,0x5b5)) {
            Unknown_005c2d10(unknown_color_7a7360,text);
            return 0;
        }
    }
    if(unknown_session_a3d298.Unknown_00672F10()) {
        int color=unknown_scheme_index_4cefc0();
        unknown_session_a3d298.Messages.Add_Message(0,0,text,color,0x16,(int)(Rules->MessageDelay*900.0),false);
    }
    wol_find_requested_name_b29cd8[0]=0;
    return 0;
    }
}
