#include "shared/wol_sink.hpp"
#include "shared/wonline_dialog_control.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
#include "shared/crt_string.hpp"
extern Wstring unknown_b2997c;
extern char buddy_query_label_008003d4[],wol_source_file_007fd62c[];
void __fastcall Set_Add_Match_Buddies_00738fa0(bool);
void __fastcall unknown_dialog_5e5f20(HWND);
// @ref ?unknown_b2997c@@3VWstring@@A=00b2997c
// @ref ?buddy_query_label_008003d4@@3PADA=008003d4
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?Set_Add_Match_Buddies_00738fa0@@YIX_N@Z=00738fa0
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
long __stdcall Buddy_Dialog_0075cc10(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    if(message==0x110 && lparam) SetWindowLongA(window,8,*(long *)(lparam+4));
    long result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(result) return result;
    OwnerDraw::DialogControl *control=(OwnerDraw::DialogControl *)GetWindowLongA(window,8);
    switch(message) {
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 1;
    case 0x14: return 1;
    case 0x2b: Unknown_005FE380(lparam); return 1;
    case 0x111:
        switch(wparam&0xffff) {
        case 1: {
            bool checked=IsDlgButtonChecked(window,0x6f9)==1;
            Set_Add_Match_Buddies_00738fa0(!checked);
            if(Unknown_00756790(unknown_b2997c)) {
                WOL::User buddy;
                memset(&buddy,0,sizeof(buddy));
                strncpy(buddy.name,unknown_b2997c.Peek_Buffer(),9);
                unknown_chat_a72cfc->unknown_slot56(&buddy);
                if(Unknown_00756790(unknown_b2997c)) {
                    Wstring copy(unknown_b2997c);
                    unknown_strings_b26920.Add(copy);
                    unknown_strings_b29838.Add(copy);
                    unknown_strings_b2a7d8.Add(copy);
                    if(unknown_wstring_b26944.Length()>0) {
                        if(time(0)-unknown_b2a7f8<5) goto updated;
                        unknown_wstring_b26944.Release();
                    }
                    if(unknown_strings_b29838.Count) {
                        if(unknown_strings_b29838.Get_007662c0(unknown_wstring_b26944,0)) unknown_strings_b29838.Remove_007661f0(0);
                        unknown_b2a7f8=time(0);
                        WOL::User user;
                        memset(&user,0,sizeof(user));
                        strcpy(user.name,unknown_wstring_b26944.Get());
                        unknown_chat_a72cfc->unknown_slot24(&user);
                    }
updated:;
                }
                Unknown_00757380();
            }
            control->Set_Window_006010f0((unsigned)window,(HWND)1);
            break;
        }
        case 2: {
            bool checked=IsDlgButtonChecked(window,0x6f9)==1;
            Set_Add_Match_Buddies_00738fa0(!checked);
            control->Set_Window_006010f0((unsigned)window,(HWND)2);
            return 0;
        }
        }
        break;
    case 0x497:
        wchar_t query[128];
        swprintf(query,StringTable::Load_String(buddy_query_label_008003d4,0,wol_source_file_007fd62c,0x69b7),unknown_b2997c.Get());
        HWND text=GetDlgItem(window,0x71b);
        SendMessageA(text,0x4b2,0,(LPARAM)query);
        return 0;
    }
    return 0;
}
