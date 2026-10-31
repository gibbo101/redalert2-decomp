#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
void __fastcall unknown_dialog_5e5f20(HWND);
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
extern "C" int __cdecl atoi(char const *);
extern Wstring unknown_wstring_b29ce4,unknown_wstring_b269a8,unknown_wstring_b2909c,unknown_wstring_b297c4;
extern int account_birth_year_b2a6d4,account_birth_day_b26930,account_birth_month_b26894,account_newsletter_b29098;
extern char wol_source_file_007fd62c[];
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?account_birth_year_b2a6d4@@3HA=00b2a6d4
// @ref ?account_birth_day_b26930@@3HA=00b26930
// @ref ?account_birth_month_b26894@@3HA=00b26894
// @ref ?account_newsletter_b29098@@3HA=00b29098
// @ref _atoi=00782d72
extern char birthdate_privacy_url_7feac0[];
// @ref ?birthdate_privacy_url_7feac0@@3PADA=007feac0
extern char birthdate_january_7feab4[];
// @ref ?birthdate_january_7feab4@@3PADA=007feab4
extern char birthdate_february_7feaa4[];
// @ref ?birthdate_february_7feaa4@@3PADA=007feaa4
extern char birthdate_march_7fea98[];
// @ref ?birthdate_march_7fea98@@3PADA=007fea98
extern char birthdate_april_7fea8c[];
// @ref ?birthdate_april_7fea8c@@3PADA=007fea8c
extern char birthdate_may_7fea84[];
// @ref ?birthdate_may_7fea84@@3PADA=007fea84
extern char birthdate_june_7fea78[];
// @ref ?birthdate_june_7fea78@@3PADA=007fea78
extern char birthdate_july_7fea6c[];
// @ref ?birthdate_july_7fea6c@@3PADA=007fea6c
extern char birthdate_august_7fea60[];
// @ref ?birthdate_august_7fea60@@3PADA=007fea60
extern char birthdate_september_7fea50[];
// @ref ?birthdate_september_7fea50@@3PADA=007fea50
extern char birthdate_october_7fea44[];
// @ref ?birthdate_october_7fea44@@3PADA=007fea44
extern char birthdate_november_7fea34[];
// @ref ?birthdate_november_7fea34@@3PADA=007fea34
extern char birthdate_december_7fea24[];
// @ref ?birthdate_december_7fea24@@3PADA=007fea24
long __stdcall Birthdate_Dialog_007494d0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    switch(message) {
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 0;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x111:
        switch(wparam&0xffff) {
        case 1: {
            unknown_wstring_b29ce4.Release();
            HWND edit=GetDlgItem(window,0x626);
            if(edit) unknown_get_window_text(edit,unknown_wstring_b29ce4);
            unknown_wstring_b269a8.Release();
            edit=GetDlgItem(window,0x62e);
            if(edit) {
                unknown_get_window_text(edit,unknown_wstring_b269a8);
                account_birth_month_b26894=atoi(unknown_wstring_b269a8.Get());
            } else account_birth_month_b26894=0;
            unknown_wstring_b2909c.Release();
            edit=GetDlgItem(window,0x62f);
            if(edit) {
                unknown_get_window_text(edit,unknown_wstring_b2909c);
                account_birth_day_b26930=atoi(unknown_wstring_b2909c.Get());
            }
            unknown_wstring_b297c4.Release();
            edit=GetDlgItem(window,0x630);
            if(edit) {
                unknown_get_window_text(edit,unknown_wstring_b297c4);
                account_birth_year_b2a6d4=atoi(unknown_wstring_b297c4.Get());
            }
            account_newsletter_b29098=0;
            edit=GetDlgItem(window,0x631);
            if(edit) account_newsletter_b29098=SendMessageA(edit,0xf0,0,0);
            Unknown_007357E0(window,1);
            return 0;
        }
        case 2:
            Unknown_007357E0(window,2);
            return 0;
        case 0x576:
            unknown_open_url_73c580(birthdate_privacy_url_7feac0,0);
            return 0;
        default:
            return 0;
        }
    case 0x497: {
        HWND edit=GetDlgItem(window,0x626);
        SendMessageA(edit,0x4d1,1,0);
        SendMessageA(GetDlgItem(window,0x62f),0xc5,2,0);
        SendMessageA(GetDlgItem(window,0x630),0xc5,4,0);
        SetFocus(GetDlgItem(window,0x62f));
        HWND month_list=GetDlgItem(window,0x62e);
        unknown_reset_combo_6007f0(month_list);
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_january_7feab4,0,wol_source_file_007fd62c,0x34bc));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_february_7feaa4,0,wol_source_file_007fd62c,0x34bd));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_march_7fea98,0,wol_source_file_007fd62c,0x34be));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_april_7fea8c,0,wol_source_file_007fd62c,0x34bf));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_may_7fea84,0,wol_source_file_007fd62c,0x34c0));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_june_7fea78,0,wol_source_file_007fd62c,0x34c1));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_july_7fea6c,0,wol_source_file_007fd62c,0x34c2));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_august_7fea60,0,wol_source_file_007fd62c,0x34c3));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_september_7fea50,0,wol_source_file_007fd62c,0x34c4));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_october_7fea44,0,wol_source_file_007fd62c,0x34c5));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_november_7fea34,0,wol_source_file_007fd62c,0x34c6));
        SendMessageA(month_list,0x4c2,0,(LPARAM)StringTable::Load_String(birthdate_december_7fea24,0,wol_source_file_007fd62c,0x34c7));
        SendDlgItemMessageA(window,0x62e,0x14e,0,0);
        SendMessageA(window,0x4a9,0,1);
        return 0;
    }
    case 0x4db:
        Unknown_005def80(lparam,wparam!=0);
        return 0;
    }
    return 0;
}
