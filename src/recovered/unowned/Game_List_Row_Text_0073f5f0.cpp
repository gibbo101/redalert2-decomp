#include "shared/wol_sink.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
WideString __fastcall User_Tooltip_0073f250(WOL::User const &user);
WideString __fastcall Unknown_0073f550(Wstring const &filename);
void __fastcall Parse_Channel_Info_0073d070(char *,int *,int *,int *,int *,int *,Wstring *);
extern "C" int __cdecl swprintf(wchar_t *,wchar_t const *,...);
extern wchar_t tooltip_separator_007f6520[];
extern char game_tooltip_empty_label_007ea8d0[],game_ping_label_007fd854[],unknown_ping_label_007fd840[];
extern char wol_source_file_007fd62c[];
// @ref ?Parse_Channel_Info_0073d070@@YIXPADPAH1111PAVWstring@@@Z=0073d070
// @ref _swprintf=00783764
// @ref ?tooltip_separator_007f6520@@3PAGA=007f6520
// @ref ?game_tooltip_empty_label_007ea8d0@@3PADA=007ea8d0
// @ref ?game_ping_label_007fd854@@3PADA=007fd854
// @ref ?unknown_ping_label_007fd840@@3PADA=007fd840
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
WideString __fastcall Game_List_Row_Text_0073f5f0(HWND list,int row)
{
    if(row==-1) return WideString(StringTable::Load_String(game_tooltip_empty_label_007ea8d0,0,wol_source_file_007fd62c,0xaa2));
    WOL::Channel channel;
    memset(&channel,0,sizeof(channel));
    int index=SendMessageA(list,0x199,row,0);
    if(index>=0 && index<unknown_games_b29990.Count) {
        channel=unknown_games_b29990.Items[index];
        Wstring host(channel.name);
        host.Truncate_At(char(0x27));
        WOL::User user;
        memset(&user,0,sizeof(user));
        strncpy(user.name,host.Get(),10);
        WideString tooltip=User_Tooltip_0073f250(user);
        tooltip+=WideString(tooltip_separator_007f6520);
        wchar_t ping_text[64];
        if(channel.ping!=-1) {
            swprintf(ping_text,StringTable::Load_String(game_ping_label_007fd854,0,wol_source_file_007fd62c,0xac4),channel.ping);
            tooltip+=ping_text;
        } else tooltip+=StringTable::Load_String(unknown_ping_label_007fd840,0,wol_source_file_007fd62c,0xac7);
        char options[132];
        strncpy(options,channel.exInfo,128);
        int version=0,checksum=0,reserved=0,observers=0,allow_observers=0;
        Wstring filename;
        Parse_Channel_Info_0073d070(options,&version,&checksum,&reserved,&observers,&allow_observers,&filename);
        if(filename.Length()>0) {
            WideString description=Unknown_0073f550(filename);
            if(description.Length()>0) {
                tooltip+=tooltip_separator_007f6520;
                tooltip+=description;
            }
        }
        return tooltip;
    }
    return WideString(StringTable::Load_String(game_tooltip_empty_label_007ea8d0,0,wol_source_file_007fd62c,0xaa9));
}
