#include "shared/wonline_dialog_control.hpp"
#include "shared/win32_api.hpp"
int __fastcall Run_Control_Dialog_006011a0(int id,DLGPROC procedure,OwnerDraw::DialogControl *control);
long __stdcall Wonline_Dialog_FE_00751190(HWND,unsigned,unsigned,long);
// @ref ?Run_Control_Dialog_006011a0@@YIHHP6GHPAUHWND__@@IIJ@ZPAVDialogControl@OwnerDraw@@@Z=006011a0
// @ref ?Wonline_Dialog_FE_00751190@@YGJPAUHWND__@@IIJ@Z=00751190
int Open_Wonline_Dialog_FE_00751130()
{
    SimpleWonlineDialogControl control;
    int result=Run_Control_Dialog_006011a0(0xfe,(DLGPROC)Wonline_Dialog_FE_00751190,&control);
    if(result<0) return 0;
    return result;
}
