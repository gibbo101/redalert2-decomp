// CNetUtilEventSink slot4, 0075D330. Original CFG: 2195 body bytes, 13 frozen NOPs.
#include "shared/wol_sink.hpp"
#include "shared/wol_ladder_list_cell.hpp"
#include "shared/string_table.hpp"
extern int ladder_column_rung_b2a800, ladder_column_name_b26c80;
extern int ladder_column_points_b297c0, ladder_column_wins_b2aafc;
extern int ladder_column_losses_b2692c, ladder_column_disconnects_b2999c;
extern int ladder_top_rung_b29ce8;
extern wchar_t const ladder_number_format_007d1598[];
extern char const ladder_empty_label_007fdb78[], ladder_source_file_007fd62c[];
void __fastcall Update_Buddy_Profile_007562b0(HWND dialog);
// @ref ?ladder_column_rung_b2a800@@3HA=00b2a800
// @ref ?ladder_column_name_b26c80@@3HA=00b26c80
// @ref ?ladder_column_points_b297c0@@3HA=00b297c0
// @ref ?ladder_column_wins_b2aafc@@3HA=00b2aafc
// @ref ?ladder_column_losses_b2692c@@3HA=00b2692c
// @ref ?ladder_column_disconnects_b2999c@@3HA=00b2999c
// @ref ?ladder_top_rung_b29ce8@@3HA=00b29ce8
// @ref ?ladder_number_format_007d1598@@3QBGB=007d1598
// @ref ?ladder_empty_label_007fdb78@@3QBDB=007fdb78
// @ref ?ladder_source_file_007fd62c@@3QBDB=007fd62c
// @ref ?Set_Ladder_007399f0@PlayerProfile@@QAEXPAULadder@WOL@@@Z=007399f0
// @ref ??_7?$rc_ptr@VPlayerProfile@@@@6B@=007af54c
// @ref ??_G?$rc_ptr@VPlayerProfile@@@@UAEPAXI@Z=0073a0c0

HRESULT __stdcall CNetUtilEventSink::OnLadderList(HRESULT result,WOL::Ladder *list,int count,long timestamp,int keyrung)
{
    if(result != S_OK) list=0;
    if(unknown_b2abd9) return S_OK;
    HWND window=GetDlgItem((HWND)Unknown_00735940(0xc1),0x57f);
    if(window && keyrung == -1 && result == S_OK) window=0;
    if(window) {
        SendMessageA(window,0x184,0,0);
        if(!list) {
            SendMessageA(window,0x4cc,-1,(LPARAM)StringTable::Load_String(ladder_empty_label_007fdb78,0,ladder_source_file_007fd62c,0xe36));
            InvalidateRect(window,0,0);
            return S_OK;
        }
    } else if(!list) return S_OK;
    WOL::Ladder *entry=list;
    wchar_t formatted[128];
    int top_rung=list->unknown_1c;
    WolLadderListCell cell;
    if(list->game_type == 0x802100) {
        if(unknown_ladder_b296f8.Count>2000) unknown_ladder_b296f8.Clear();
    } else if(list->game_type == 0x2300) {
        if(unknown_ladder_b26970.Count>2000) unknown_ladder_b26970.Clear();
    } else {
        if(unknown_ladder_b2ab98.Count>2000) unknown_ladder_b2ab98.Clear();
    }
    if(list && window) ladder_top_rung_b29ce8=list->unknown_1c;
    Wstring local_name=unknown_wstring_b26cb8.As_Lower();
    int row=0;
    while(entry) {
        if(entry->unknown_10 == -1) {
            entry=entry->next;
            continue;
        }
        if(window) {
            cell.Flags=4;
            swprintf(formatted,ladder_number_format_007d1598,entry->unknown_1c);
            SendMessageA(window,0x4cc,-1,(LPARAM)formatted);
            SendMessageA(window,0x4a8,((unsigned short)ladder_column_rung_b2a800 | ((unsigned int)(unsigned short)row << 16)),(LPARAM)&cell);
            cell.Flags=1;
            wchar_t wide_name[5120];
            Unknown_006FA0C0(wide_name,entry->name,-1);
            cell.Text.Set(wide_name);
            SendMessageA(window,0x4a8,((unsigned short)ladder_column_name_b26c80 | ((unsigned int)(unsigned short)row << 16)),(LPARAM)&cell);
            swprintf(formatted,ladder_number_format_007d1598,entry->unknown_10);
            cell.Text.Set(formatted);
            SendMessageA(window,0x4a8,((unsigned short)ladder_column_points_b297c0 | ((unsigned int)(unsigned short)row << 16)),(LPARAM)&cell);
            swprintf(formatted,ladder_number_format_007d1598,entry->unknown_08);
            cell.Text.Set(formatted);
            SendMessageA(window,0x4a8,((unsigned short)ladder_column_wins_b2aafc | ((unsigned int)(unsigned short)row << 16)),(LPARAM)&cell);
            swprintf(formatted,ladder_number_format_007d1598,entry->unknown_0c);
            cell.Text.Set(formatted);
            SendMessageA(window,0x4a8,((unsigned short)ladder_column_losses_b2692c | ((unsigned int)(unsigned short)row << 16)),(LPARAM)&cell);
            swprintf(formatted,ladder_number_format_007d1598,entry->unknown_20);
            cell.Text.Set(formatted);
            SendMessageA(window,0x4a8,((unsigned short)ladder_column_disconnects_b2999c | ((unsigned int)(unsigned short)row << 16)),(LPARAM)&cell);
            ++row;
        }
        Wstring name(entry->name);
        name.To_Lower();
        if(list->game_type == 0x802100) {
            WOL::Ladder old_value;
            unknown_ladder_b296f8.Remove_00767160(name,&old_value);
            unknown_ladder_b296f8.Add(name,*entry);
        }
        else if(list->game_type == 0x2300) {
            WOL::Ladder old_value;
            unknown_ladder_b26970.Remove_00767160(name,&old_value);
            unknown_ladder_b26970.Add(name,*entry);
        }
        else {
            WOL::Ladder old_value;
            unknown_ladder_b2ab98.Remove_00767160(name,&old_value);
            unknown_ladder_b2ab98.Add(name,*entry);
        }
        if(local_name == name) {
            rc_ptr<PlayerProfile> profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
            if(profile.Get()) {
                profile->Set_Ladder_007399f0(entry);
                profile->Save_007395d0(name);
                HWND dialog=(HWND)Unknown_00735940(0x10e);
                if(!dialog) dialog=(HWND)Unknown_00735940(0x114);
                if(dialog) profile->Populate_Dialog_00739b70(dialog,unknown_wstring_b26cb8,false);
            }
        }
        entry=entry->next;
    }
    if(window) {
        SendMessageA(window,0x186,keyrung-top_rung,0);
        InvalidateRect(window,0,0);
    } else Unknown_0073FEE0(0,false);
    Unknown_00757380();
    HWND buddy=(HWND)Unknown_00735940(0x116);
    if(buddy) Update_Buddy_Profile_007562b0(buddy);
    return S_OK;
}

// @ref ?unknown_ladder_b26970@@3VWolLadderCache@@A=00b26970
// @ref ?unknown_ladder_b2ab98@@3VWolLadderCache@@A=00b2ab98
