#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/owner_draw_dialog_control.hpp"
extern "C" __declspec(dllimport) UINT __stdcall IsDlgButtonChecked(HWND,int);
// @ref __imp__IsDlgButtonChecked@8=0079a408
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall Wait_Paint_005e5f20(HWND);
void __fastcall Set_Auto_Login_00738da0(bool value);
void __fastcall Unknown_007391f0(Wstring const &name);
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Wait_Paint_005e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?Set_Auto_Login_00738da0@@YIX_N@Z=00738da0
// @ref ?Unknown_007391f0@@YIXABVWstring@@@Z=007391f0
long __stdcall Auto_Login_Confirmation_Dialog_00755070(HWND window,unsigned message,unsigned wparam,long lparam)
{
    if(message==0x110 && lparam) SetWindowLongA(window,8,*(long *)(lparam+4));
    int handled=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(handled) return handled;
    OwnerDraw::DialogControl *control=(OwnerDraw::DialogControl *)GetWindowLongA(window,8);
    switch(message) {
    case 0x111:
        switch(wparam & 0xffff) {
        case 1:
            Unknown_007391f0(unknown_wstring_b26cb8);
            control->Set_Window_006010f0((unsigned)window,(HWND)1);
            break;
        case 2:
            {
                bool checked=IsDlgButtonChecked(window,0x6f9)==1;
                Set_Auto_Login_00738da0(!checked);
                control->Set_Window_006010f0((unsigned)window,(HWND)2);
            }
            return 0;
        }
        break;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x14: return 1;
    case 0xf:
        Unknown_005FEE70(window);
        Wait_Paint_005e5f20(window);
        ValidateRect(window,0);
        return 1;
    }
    return 0;
}
