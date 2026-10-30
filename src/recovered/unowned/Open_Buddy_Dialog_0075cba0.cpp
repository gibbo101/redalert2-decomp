#include "shared/wol_sink.hpp"
#include "shared/wonline_dialog_control.hpp"
#include "shared/win32_api.hpp"
extern Wstring unknown_b2997c;
// @ref ?unknown_b2997c@@3VWstring@@A=00b2997c
bool Unknown_00738eb0();
int __fastcall Run_Control_Dialog_006011a0(int,DLGPROC,OwnerDraw::DialogControl *);
long __stdcall Buddy_Dialog_0075cc10(HWND,unsigned,unsigned,long);
// @ref ?Unknown_00738eb0@@YA_NXZ=00738eb0
// @ref ?Run_Control_Dialog_006011a0@@YIHHP6GHPAUHWND__@@IIJ@ZPAVDialogControl@OwnerDraw@@@Z=006011a0
// @ref ?Buddy_Dialog_0075cc10@@YGJPAUHWND__@@IIJ@Z=0075cc10
void Open_Buddy_Dialog_0075cba0()
{
    unknown_b2abd9=false;
    if(!unknown_b2abda && Unknown_00738eb0() && Unknown_00756790(unknown_b2997c)) {
        SimpleWonlineDialogControl control;
        Run_Control_Dialog_006011a0(0x122,(DLGPROC)Buddy_Dialog_0075cc10,&control);
    }
}
