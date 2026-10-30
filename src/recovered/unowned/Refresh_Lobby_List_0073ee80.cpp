#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/wol_ladder_list_cell.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl swprintf(wchar_t *,wchar_t const *,...);
extern "C" long __cdecl atol(char const *);
long __fastcall unknown_get_window_item_text(HWND,unsigned int,Wstring &);
int __fastcall unknown_clear_listbox(HWND);
extern char lobby_prefix_007fd358[];
extern wchar_t lobby_first_page_format_007fd7f4[],lobby_later_page_format_007fd7dc[];
extern unsigned int lobby_title_column_b29acc;
// @ref _swprintf=00783764
// @ref ?lobby_prefix_007fd358@@3PADA=007fd358
// @ref ?lobby_first_page_format_007fd7f4@@3PAGA=007fd7f4
// @ref ?lobby_later_page_format_007fd7dc@@3PAGA=007fd7dc
// @ref ?lobby_title_column_b29acc@@3IA=00b29acc
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
void __fastcall Refresh_Lobby_List_0073ee80()
{
    HWND dialog=(HWND)Unknown_00735940(0x113);
    if(!dialog) return;
    HWND list=GetDlgItem(dialog,0x53d);
    if(!list) return;
    Wstring selected;
    int selected_row=SendMessageA(list,0x18e,0,0);
    if(selected_row!=-1) unknown_get_window_item_text(list,selected_row,selected);
    SendMessageA(list,0x49d,0,1);
    unknown_clear_listbox(list);
    int count=unknown_lobbies_b26c88.Count;
    for(int i=0;i<count;++i) {
        WOL::Channel channel;
        unknown_lobbies_b26c88.Get(channel,i);
        if(strncmp(channel.name,lobby_prefix_007fd358,strlen(lobby_prefix_007fd358))!=0) continue;
        int number=atol(channel.name+strlen(lobby_prefix_007fd358));
        bool current=strcmp(channel.name,unknown_game_channel_b299c0.name)==0;
        wchar_t title[80];
        int page=number/8;
        int name_index=number%8;
        if(page==0) swprintf(title,lobby_first_page_format_007fd7f4,(wchar_t const *)unknown_lobby_names_b26c94[name_index],channel.currentUsers);
        else swprintf(title,lobby_later_page_format_007fd7dc,(wchar_t const *)unknown_lobby_names_b26c94[name_index],page+1,channel.currentUsers);
        int rows=SendMessageA(list,0x18b,0,0);
        int at=0;
        WOL::Channel other;
        for(;at<rows;++at) {
            int index=SendMessageA(list,0x199,at,0);
            unknown_lobbies_b26c88.Get(other,index);
            if(atol(other.name+strlen(lobby_prefix_007fd358))>number) break;
        }
        int row=SendMessageA(list,0x4c7,at,(LPARAM)channel.name);
        SendMessageA(list,0x19a,row,i);
        WolLadderListCell cell;
        cell.Flags=1;
        cell.Text.Set(title);
        cell.Secondary.Set(L"");
        SendMessageA(list,0x4a8,(unsigned short)lobby_title_column_b29acc|((unsigned long)(unsigned short)row<<16),(LPARAM)&cell);
        if(current) SendMessageA(list,0x186,row,0);
    }
    int restored=SendMessageA(list,0x4c5,0,(LPARAM)selected.Peek_Buffer());
    if(restored!=-1) SendMessageA(list,0x197,restored,0);
    SendMessageA(list,0x49d,0,0);
    InvalidateRect(list,0,false);
}
