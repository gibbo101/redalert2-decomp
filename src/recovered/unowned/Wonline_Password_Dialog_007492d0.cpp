#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
extern char password_invalid_characters_7fea20[];
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?password_invalid_characters_7fea20@@3PADA=007fea20
long __stdcall Wonline_Password_Dialog_007492d0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    if(message==0x110 && lparam) SetWindowLongA(window,8,*(long *)(lparam+4));
    int handled=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(handled) return handled;
    WonlineStringDialogControl *control=(WonlineStringDialogControl *)GetWindowLongA(window,8);
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
            Wstring password;
            unknown_get_window_text(GetDlgItem(window,0x72c),password);
            control->Text=password;
            control->Set_Window_006010f0((unsigned)window,(HWND)1);
            return 0;
        }
        case 2:
            control->Set_Window_006010f0((unsigned)window,(HWND)2);
            return 0;
        case 0x72c:
            if(lparam) {
                Wstring password;
                unknown_get_window_text((HWND)lparam,password);
                EnableWindow(GetDlgItem(window,1),!password.Contains_Any(password_invalid_characters_7fea20));
            }
            return 0;
        }
        break;
    case 0x497: {
        HWND edit=GetDlgItem(window,0x72c);
        SendMessageA(edit,0x4d1,1,0);
        edit=GetDlgItem(window,0x72c);
        SendMessageA(edit,0x4b4,0,(LPARAM)unknown_string_83c55c);
        SendDlgItemMessageA(window,0x72c,0xc5,8,0);
        SetFocus(GetDlgItem(window,0x72c));
        return 0;
    }
    case 0x4da:
        PostMessageA(GetDlgItem(window,1),0xf5,0,0);
        return 0;
    }
    return 0;
}
