#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/wol_ladder_list_cell.hpp"
#include "shared/crt_string.hpp"
#include "shared/string_table.hpp"
extern "C" int __cdecl swprintf(wchar_t *,wchar_t const *,...);
long __fastcall unknown_get_window_item_text(HWND,unsigned int,Wstring &);
void __fastcall Parse_Channel_Info_0073d070(char *,int *,int *,int *,int *,int *,Wstring *);
extern bool game_list_refreshing_b2ac80;
extern unsigned int game_name_column_b2a8a8,game_type_column_b2a6f8,game_private_column_b2a6f4,game_observer_column_b299a0,game_ping_column_b292a8;
extern int game_unavailable_color_007a7380;
extern wchar_t game_counts_format_007fd8b8[],game_unknown_ping_text_007fd874[];
extern char game_clan_image_007eb228[],game_tournament_image_007eb25c[],game_normal_image_007eb1fc[],game_private_image_007eb234[];
extern char game_locked_observer_image_007eb218[],game_locked_image_007eafb4[],game_observer_image_007e7444[];
extern char game_clan_label_007fd8a4[],game_tournament_label_007fd890[],game_password_label_007fd87c[],game_ping_label_007fd864[],wol_source_file_007fd62c[];
// @ref _swprintf=00783764
// @ref ?Parse_Channel_Info_0073d070@@YIXPADPAH1111PAVWstring@@@Z=0073d070
// @ref ?game_list_refreshing_b2ac80@@3_NA=00b2ac80
// @ref ?game_name_column_b2a8a8@@3IA=00b2a8a8
// @ref ?game_type_column_b2a6f8@@3IA=00b2a6f8
// @ref ?game_private_column_b2a6f4@@3IA=00b2a6f4
// @ref ?game_observer_column_b299a0@@3IA=00b299a0
// @ref ?game_ping_column_b292a8@@3IA=00b292a8
// @ref ?game_unavailable_color_007a7380@@3HA=007a7380
// @ref ?game_counts_format_007fd8b8@@3PAGA=007fd8b8
// @ref ?game_unknown_ping_text_007fd874@@3PAGA=007fd874
// @ref ?game_clan_image_007eb228@@3PADA=007eb228
// @ref ?game_tournament_image_007eb25c@@3PADA=007eb25c
// @ref ?game_normal_image_007eb1fc@@3PADA=007eb1fc
// @ref ?game_private_image_007eb234@@3PADA=007eb234
// @ref ?game_locked_observer_image_007eb218@@3PADA=007eb218
// @ref ?game_locked_image_007eafb4@@3PADA=007eafb4
// @ref ?game_observer_image_007e7444@@3PADA=007e7444
// @ref ?game_clan_label_007fd8a4@@3PADA=007fd8a4
// @ref ?game_tournament_label_007fd890@@3PADA=007fd890
// @ref ?game_password_label_007fd87c@@3PADA=007fd87c
// @ref ?game_ping_label_007fd864@@3PADA=007fd864
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
void __fastcall Refresh_Game_List_0073f8f0()
{
    HWND dialog=(HWND)Unknown_00735940(0x113);
    if(!dialog) return;
    HWND list=GetDlgItem(dialog,0x6ee);
    if(!list) return;
    Wstring previous_selection;
    int selected=SendMessageA(list,0x188,0,0);
    if(selected!=-1) unknown_get_window_item_text(list,selected,previous_selection);
    Wstring previous_top;
    int top=SendMessageA(list,0x18e,0,0);
    if(top!=-1) unknown_get_window_item_text(list,top,previous_top);
    SendMessageA(list,0x49d,0,1);
    game_list_refreshing_b2ac80=true;
    SendMessageA(list,0x184,0,0);
    int count=unknown_games_b29990.Count;
    for(int i=0;i<count;++i) {
        WOL::Channel channel;
        memset(&channel,0,sizeof(channel));
        unknown_games_b29990.Get(channel,i);
        if(Unknown_0073c3e0(&channel) || Unknown_0073c400(&channel)) continue;
        char options[132];
        strncpy(options,channel.exInfo,128);
        int version=0,checksum=0,extra_players=0,observers=0,allow_observers=0;
        Wstring filename;
        Parse_Channel_Info_0073d070(options,&version,&checksum,&extra_players,&observers,&allow_observers,&filename);
        int participants=channel.currentUsers-observers+extra_players;
        int capacity=channel.maxUsers-((observers || allow_observers) ? 1 : 0);
        wchar_t title[80];
        swprintf(title,game_counts_format_007fd8b8,channel.name,participants,capacity);
        int row=SendMessageA(list,0x4c7,-1,(LPARAM)channel.name);
        SendMessageA(list,0x19a,row,i);
        WolLadderListCell cell;
        cell.Flags=1;
        cell.Text.Set(title);
        cell.Secondary.Set(L"");
        cell.unknown_0c=unknown_color_7a7360;
        if(unknown_a72c68) {
            if(!allow_observers || observers) cell.unknown_0c=game_unavailable_color_007a7380;
        } else if(participants==capacity) cell.unknown_0c=game_unavailable_color_007a7380;
        SendMessageA(list,0x4a8,((unsigned long)(unsigned short)game_name_column_b2a8a8|((unsigned long)(unsigned short)row<<16)),(LPARAM)&cell);
        cell.Flags=0;
        cell.Secondary.Set(L"");
        cell.Flags=2;
        cell.Secondary.Set(L"");
        if(Unknown_0073c3c0(&channel)) {
            cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(game_clan_image_007eb228,0);
            cell.Secondary.Set(StringTable::Load_String(game_clan_label_007fd8a4,0,wol_source_file_007fd62c,0xb57));
        } else if(Unknown_0073c340(&channel)) {
            cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(game_tournament_image_007eb25c,0);
            cell.Secondary.Set(StringTable::Load_String(game_tournament_label_007fd890,0,wol_source_file_007fd62c,0xb5c));
        } else {
            cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(game_normal_image_007eb1fc,0);
            cell.Secondary.Set(L"");
        }
        SendMessageA(list,0x4a8,((unsigned long)(unsigned short)game_type_column_b2a6f8|((unsigned long)(unsigned short)row<<16)),(LPARAM)&cell);
        cell.Flags=2;
        cell.Secondary.Set(L"");
        if(channel.flags&0x100) {
            cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(game_private_image_007eb234,0);
            cell.Secondary.Set(StringTable::Load_String(game_password_label_007fd87c,0,wol_source_file_007fd62c,0xb6a));
        } else {
            cell.Flags=0;
            cell.Secondary.Set(L"");
        }
        SendMessageA(list,0x4a8,((unsigned long)(unsigned short)game_private_column_b2a6f4|((unsigned long)(unsigned short)row<<16)),(LPARAM)&cell);
        cell.Flags=0;
        cell.Text.Set(L"");
        cell.Secondary.Set(L"");
        if(channel.unknown_20&0x600) {
            if(!observers && allow_observers) {
                cell.Flags=2;
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(game_locked_observer_image_007eb218,0);
            } else {
                cell.Flags=2;
                cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(game_locked_image_007eafb4,0);
            }
        } else if(!observers && allow_observers) {
            cell.Flags=2;
            cell.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(game_observer_image_007e7444,0);
        }
        SendMessageA(list,0x4a8,((unsigned long)(unsigned short)game_observer_column_b299a0|((unsigned long)(unsigned short)row<<16)),(LPARAM)&cell);
        if(channel.ping==-1) {
            cell.Flags=1;
            cell.Text.Set(game_unknown_ping_text_007fd874);
        } else {
            cell.unknown_14=channel.ping;
            cell.Flags=3;
        }
        swprintf(title,StringTable::Load_String(game_ping_label_007fd864,0,wol_source_file_007fd62c,0xb92),channel.ping);
        cell.Secondary.Set(title);
        SendMessageA(list,0x4a8,((unsigned long)(unsigned short)game_ping_column_b292a8|((unsigned long)(unsigned short)row<<16)),(LPARAM)&cell);
    }
    int restored=SendMessageA(list,0x4c5,0,(LPARAM)previous_selection.Peek_Buffer());
    SendMessageA(list,0x186,restored,0);
    int restored_top=SendMessageA(list,0x4c5,0,(LPARAM)previous_top.Peek_Buffer());
    if(restored_top!=-1) SendMessageA(list,0x197,restored_top,0);
    SendMessageA(list,0x49d,0,0);
    InvalidateRect(list,0,false);
    if(dialog==Unknown_00735B10()) SetFocus(GetDlgItem(dialog,0x540));
}
