#include "shared/wol_sink.hpp"
#include "shared/mouse.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
LRESULT __fastcall unknown_get_window_wide_text(HWND,WideString &);
extern unsigned short wol_empty_text_839d4c[];
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?wol_empty_text_839d4c@@3PAGA=00839d4c
// @ref ??_C@_15MLJJ@?$AA?6?$AA?$AN?$AA?$AA@=007e7404
// @ref ??_C@_1BC@HKMH@?$AA?$FL?$AA?$CF?$AAh?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007fe9a4
int WINAPI Page_Dialog_Proc_00757d80(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    WOL::User user;
    int result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
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
        switch((int)(wparam&0xffff)) {
        case 0x540:
            switch((unsigned short)(wparam>>16)) {
            case 0x300: {
                WideString text;
                unknown_get_window_wide_text((HWND)lparam,text);
                EnableWindow(GetDlgItem(window,0x5c2),0<text.Length());
                return 0;
            }
            case 0x400: {
                WideString text;
                unknown_get_window_wide_text((HWND)lparam,text);
                text.Trim_Trailing(L"\n\r");
                return 0;
            }
            case 0x501: {
                WideString text;
                unknown_get_window_wide_text((HWND)lparam,text);
                text.Trim_Trailing(L"\n\r");
                if(text.Length()>0) SendMessageA(GetDlgItem(window,0x5c2),0xf5,0,0);
                return 0;
            }
            }
            break;
        case 0x53f:
            switch((unsigned short)(wparam>>16)) { case 1: {
                Wstring recipient=Unknown_00757cc0((HWND)lparam);
                HWND target=GetDlgItem(window,0x718);
                SendMessageA(target,0x4b4,0,(LPARAM)recipient.Peek_Buffer());
            } break; }
            break;
        case 0x5c2: {
            WideString text;
            HWND edit=GetDlgItem(window,0x540);
            unknown_get_window_wide_text(edit,text);
            SendMessageA(edit,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
            Wstring recipient=Unknown_00757cc0(GetDlgItem(window,0x53f));
            if(recipient.Length()>0 && text.Length()>0) {
                text.Trim_Trailing(L"\n\r");
                memset(&user,0,sizeof(user));
                strcpy(user.name,recipient.Get());
                unknown_chat_a72cfc->unknown_slot62(&user,text.Get());
                Unknown_005C2C80(unknown_color_7a7364,L"[%hs] %s",unknown_wstring_b26cb8.Buffer,text.Get());
            }
            EnableWindow((HWND)lparam,0);
            InvalidateRect(edit,0,0);
            break;
        }
        case 0x686:
            Unknown_007357E0(window,0x5c2);
            break;
        }
        break;
    case 0x497: {
        HWND edit=GetDlgItem(window,0x540);
        SendMessageA(edit,0xc5,0x78,0);
        SendMessageA(edit,0x4b2,0,(LPARAM)wol_empty_text_839d4c);
        EnableWindow(GetDlgItem(window,0x5c2),0);
        Set_Edit_Text(GetDlgItem(window,0x718),Unknown_00757cc0(GetDlgItem(window,0x53f)));
        if(WWMouse) WWMouse->Release_Mouse();
        break;
    }
    }
    return 0;
}
