#include "shared/wol_sink.hpp"
extern "C" int __cdecl swprintf(wchar_t *,wchar_t const *,...);
WideString __fastcall unknown_number_text_7710c0(int number);
extern char wol_profile_label_7fd2d8[],wol_profile_unranked_7fd2c4[],wol_source_file_007fd62c[];
extern unsigned short wol_empty_text_839d4c[];
// @ref ?wol_profile_label_7fd2d8@@3PADA=007fd2d8
// @ref ?wol_profile_unranked_7fd2c4@@3PADA=007fd2c4
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_empty_text_839d4c@@3PAGA=00839d4c
// @ref _swprintf=00783764
void __fastcall Update_Buddy_Profile_007562b0(HWND dialog)
{
    HWND label=GetDlgItem(dialog,0x6ef);
    HWND rank=GetDlgItem(dialog,0x6f4);
    HWND points=GetDlgItem(dialog,0x6f5);
    HWND wins=GetDlgItem(dialog,0x6f0);
    HWND losses=GetDlgItem(dialog,0x6f1);
    HWND disconnects=GetDlgItem(dialog,0x701);
    if(unknown_wstring_b29cd4.Length()==0) {
        SendMessageA(label,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
        SendMessageA(rank,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
        SendMessageA(points,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
        SendMessageA(wins,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
        SendMessageA(losses,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
        SendMessageA(disconnects,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
        return;
    }
    WideString format(StringTable::Load_String(wol_profile_label_7fd2d8,0,wol_source_file_007fd62c,0x607c));
    unsigned length=format.Length()+unknown_wstring_b29cd4.Length();
    wchar_t *text=new wchar_t[length+1];
    swprintf(text,(wchar_t const *)format.Get(),unknown_wstring_b29cd4.Get());
    HWND title=GetDlgItem(dialog,0x6ef);
    SendMessageA(title,0x4b2,0,(LPARAM)text);
    delete [] text;
    WOL::Ladder entry;
    memset(&entry,0,sizeof(entry));
    Wstring name=unknown_wstring_b29cd4.As_Lower();
    bool found;
    {
        WOL::Ladder *value=0;
        found=unknown_ladder_b2ab98.Get_Pointer_007670f0(name,&value);
        if(found && value) entry=*value;
    }
    if(found) {
        SendMessageA(rank,0x4b2,0,(LPARAM)unknown_number_text_7710c0(entry.unknown_1c).unknown_text_770430());
        SendMessageA(points,0x4b2,0,(LPARAM)unknown_number_text_7710c0(entry.unknown_10).unknown_text_770430());
        SendMessageA(wins,0x4b2,0,(LPARAM)unknown_number_text_7710c0(entry.unknown_08).unknown_text_770430());
        SendMessageA(losses,0x4b2,0,(LPARAM)unknown_number_text_7710c0(entry.unknown_0c).unknown_text_770430());
        SendMessageA(disconnects,0x4b2,0,(LPARAM)unknown_number_text_7710c0(entry.unknown_20).unknown_text_770430());
    } else {
        WideString unranked(StringTable::Load_String(wol_profile_unranked_7fd2c4,0,wol_source_file_007fd62c,0x608d));
        SendMessageA(rank,0x4b2,0,(LPARAM)unranked.unknown_text_770430());
        SendMessageA(points,0x4b2,0,(LPARAM)unranked.unknown_text_770430());
        SendMessageA(wins,0x4b2,0,(LPARAM)unranked.unknown_text_770430());
        SendMessageA(losses,0x4b2,0,(LPARAM)unranked.unknown_text_770430());
        SendMessageA(disconnects,0x4b2,0,(LPARAM)unranked.unknown_text_770430());
    }
}
