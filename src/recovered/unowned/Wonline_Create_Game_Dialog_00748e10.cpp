#include "shared/wol_sink.hpp"
#include "shared/unknown_globals.hpp"
// RTTI COL0x007C6490 names CreateGameDialogControl; vtable0x007AF94C.
// Constructor0x007459A0 and this dialog establish four flag bytes after Text.
class CreateGameDialogControl : public WonlineStringDialogControl {
public:
    virtual ~CreateGameDialogControl();
    bool unknown_10,unknown_11,unknown_12,unknown_13;
};
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
extern "C" __declspec(dllimport) UINT __stdcall IsDlgButtonChecked(HWND,int);
extern "C" __declspec(dllimport) BOOL __stdcall CheckDlgButton(HWND,int,UINT);
// @ref __imp__IsDlgButtonChecked@8=0079a408
// @ref __imp__CheckDlgButton@12=0079a40c
extern int wol_max_players_b2abdc;
extern char wol_empty_name_83c55c[],wol_password_forbidden_7fea20[];
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?wol_max_players_b2abdc@@3HA=00b2abdc
// @ref ?wol_empty_name_83c55c@@3PADA=0083c55c
// @ref ?wol_password_forbidden_7fea20@@3PADA=007fea20
long __stdcall Wonline_Create_Game_Dialog_00748e10(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    if(message==0x110 && lparam) SetWindowLongA(window,8,*(long *)(lparam+4));
    long result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(result) return result;
    CreateGameDialogControl *control=(CreateGameDialogControl *)GetWindowLongA(window,8);
    switch(message) {
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
        return 0;
    case 0x14: return 1;
    case 0x2b: Unknown_005FE380(lparam); return 1;
    case 0x111:
        switch((int)(wparam&0xffff)) {
        case 1: {
            wol_max_players_b2abdc=5;
            Wstring password;
            unknown_get_window_text(GetDlgItem(window,0x72c),password);
            control->Text=password;
            control->Set_Window_006010f0((unsigned)window,(HWND)1);
            return 0;
        }
        case 2:
            control->Set_Window_006010f0((unsigned)window,(HWND)2);
            return 0;
        case 0x629:
            if(SendDlgItemMessageA(window,0x629,0xf0,0,0)==1) {
                SendDlgItemMessageA(window,0x66c,0xf1,0,0);
                control->unknown_11=false;
                control->unknown_10=true;
            } else control->unknown_10=false;
            return 0;
        case 0x66c:
            if(SendDlgItemMessageA(window,0x66c,0xf0,0,0)==1) {
                SendDlgItemMessageA(window,0x629,0xf1,0,0);
                control->unknown_11=true;
                control->unknown_10=false;
            } else control->unknown_11=false;
            return 0;
        case 0x6df:
            if(IsDlgButtonChecked(window,0x6e0)) CheckDlgButton(window,0x6e0,0);
            else CheckDlgButton(window,0x6df,1);
            return 0;
        case 0x72c:
            if(lparam) {
                Wstring password;
                unknown_get_window_text((HWND)lparam,password);
                EnableWindow(GetDlgItem(window,1),!password.Contains_Any(wol_password_forbidden_7fea20));
            }
            return 0;
        case 0x6e0:
            if(IsDlgButtonChecked(window,0x6df)) CheckDlgButton(window,0x6df,0);
            else CheckDlgButton(window,0x6e0,1);
            return 0;
        case 0x71e:
            control->unknown_12=SendMessageA((HWND)lparam,0xf0,0,0)==1;
            return 0;
        case 0x71f:
            control->unknown_13=SendMessageA((HWND)lparam,0xf0,0,0)==1;
            return 0;
        }
        break;
    case 0x497: {
        HWND password=GetDlgItem(window,0x72c);
        SendMessageA(password,0x4d1,1,0);
        password=GetDlgItem(window,0x72c);
        SendMessageA(password,0x4b4,0,(LPARAM)wol_empty_name_83c55c);
        SendDlgItemMessageA(window,0x72c,0xc5,8,0);
        SetFocus(GetDlgItem(window,0x72c));
        CheckDlgButton(window,0x629,control->unknown_10!=false);
        CheckDlgButton(window,0x66c,control->unknown_11!=false);
        if((unknown_game_mode_a3d298!=4 || unknown_a3d2a4!=2) && (int)unknown_squad_id_b2abfc<1)
            EnableWindow(GetDlgItem(window,0x66c),0);
        HWND resolution=GetDlgItem(window,0x71e);
        bool high_resolution=unknown_8523e0>=1024;
        EnableWindow(resolution,!high_resolution);
        SendMessageA(resolution,0xf1,control->unknown_12 && !high_resolution ? 1:0,0);
        HWND unknown_option=GetDlgItem(window,0x71f);
        SendMessageA(unknown_option,0xf1,control->unknown_13!=false,0);
        break;
    }
    case 0x4da:
        PostMessageA(GetDlgItem(window,1),0xf5,0,0);
        return 0;
    }
    return 0;
}
