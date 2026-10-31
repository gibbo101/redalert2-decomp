#include "shared/wol_sink.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
LRESULT __fastcall unknown_get_window_wide_text(HWND,WideString &);
extern unsigned short wol_empty_text_839d4c[];
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?wol_empty_text_839d4c@@3PAGA=00839d4c
// @ref ??_C@_15MLJJ@?$AA?6?$AA?$AN?$AA?$AA@=007e7404
long __stdcall Buddy_Message_Dialog_00757950(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    long result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(result) return result;
    switch(message) {
    case 2: return 0;
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 1;
    case 0x14: return 1;
    case 0x2b: Unknown_005FE380(lparam); return 1;
    case 0x111:
        switch(wparam&0xffff) {
        case 0x540:
            switch(wparam>>16) {
            case 0x300: {
                WideString text;
                unknown_get_window_wide_text((HWND)lparam,text);
                EnableWindow(GetDlgItem(window,0x5c2),0<text.Length());
                break;
            }
            case 0x400: {
                WideString text;
                unknown_get_window_wide_text((HWND)lparam,text);
                text.Trim_Trailing(L"\n\r");
                return 0;
            }
            case 0x501:
                SendMessageA(GetDlgItem(window,0x5c2),0xf5,0,0);
                break;
            }
            break;
        case 0x5c2: {
            WideString text;
            HWND edit=GetDlgItem(window,0x540);
            unknown_get_window_wide_text(edit,text);
            SendMessageA(edit,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
            if(text.Length()>0) {
                text.Trim_Trailing(L"\n\r");
                WOL::User user;
                memset(&user,0,sizeof(user));
                strcpy(user.name,unknown_wstring_b29cd4.Get());
                unknown_chat_a72cfc->unknown_slot62(&user,text.Get());
            }
            InvalidateRect(edit,0,0);
            Unknown_007357E0(window,0x5c2);
            break;
        }
        case 0x686:
            Unknown_007357E0(window,0x686);
            break;
        }
        break;
    case 0x497: {
        HWND edit=GetDlgItem(window,0x540);
        SendMessageA(edit,0xc5,0x78,0);
        SendMessageA(edit,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
        EnableWindow(GetDlgItem(window,0x5c2),0);
        HWND name=GetDlgItem(window,0x712);
        SendMessageA(name,0x4b4,0,(LPARAM)unknown_wstring_b29cd4.Peek_Buffer());
        break;
    }
    }
    return 0;
}
