#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/owner_draw_dialog_control.hpp"
namespace OwnerDraw { int __fastcall unknown_5eab00(HWND control); }
void __fastcall unknown_dialog_5e5f20(HWND);
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
extern Wstring account_name_b2a640,account_password_b2a71c,account_password_check_b2a724,unknown_account_detail_b2945c;
extern int unknown_account_checkbox_b29ad0;
extern unsigned int unknown_account_input_events_b2ac98;
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?account_name_b2a640@@3VWstring@@A=00b2a640
// @ref ?account_password_b2a71c@@3VWstring@@A=00b2a71c
// @ref ?account_password_check_b2a724@@3VWstring@@A=00b2a724
// @ref ?unknown_account_detail_b2945c@@3VWstring@@A=00b2945c
// @ref ?unknown_account_checkbox_b29ad0@@3HA=00b29ad0
// @ref ?unknown_account_input_events_b2ac98@@3IA=00b2ac98
long __stdcall Account_Details_Dialog_007498e0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    switch(message) {
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 0;
    case 0x2b: Unknown_005FE380(lparam); return 1;
    case 0x111:
        switch(wparam&0xffff) {
        case 1: {
            int kind=OwnerDraw::unknown_5eab00(window);
            account_name_b2a640.Release();
            HWND edit=GetDlgItem(window,0x628);
            if(edit) unknown_get_window_text(edit,account_name_b2a640);
            account_password_b2a71c.Release();
            edit=GetDlgItem(window,0x72c);
            if(edit) unknown_get_window_text(edit,account_password_b2a71c);
            account_password_check_b2a724.Release();
            edit=GetDlgItem(window,0x627);
            if(edit) unknown_get_window_text(edit,account_password_check_b2a724);
            if(kind==0xf3) {
                unknown_account_detail_b2945c.Release();
                edit=GetDlgItem(window,0x5e5);
                if(edit) unknown_get_window_text(edit,unknown_account_detail_b2945c);
            } else if(kind==0xf4) {
                unknown_account_checkbox_b29ad0=0;
                edit=GetDlgItem(window,0x66b);
                if(edit) unknown_account_checkbox_b29ad0=SendMessageA(edit,0xf0,0,0);
            }
            Unknown_007357E0(window,1);
            return 0;
        }
        case 2:
            Unknown_007357E0(window,2);
            return 0;
        }
        break;
    case 0x497: {
        HWND edit=GetDlgItem(window,0x628);
        SendMessageA(edit,0x4d1,1,0);
        edit=GetDlgItem(window,0x72c);
        SendMessageA(edit,0x4d1,1,0);
        edit=GetDlgItem(window,0x627);
        SendMessageA(edit,0x4d1,1,0);
        edit=GetDlgItem(window,0x5e5);
        SendMessageA(edit,0x4d1,1,0);
        SendMessageA(GetDlgItem(window,0x628),0xc5,9,0);
        SendMessageA(GetDlgItem(window,0x72c),0xc5,8,0);
        SendMessageA(GetDlgItem(window,0x627),0xc5,8,0);
        SetFocus(GetDlgItem(window,0x628));
        break;
    }
    case 0x4db:
        ++unknown_account_input_events_b2ac98;
        Unknown_005def80(lparam,wparam!=0);
        return 0;
    }
    return 0;
}
