#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/wonline_dialog_control.hpp"
#include "shared/crt_string.hpp"
extern unsigned int unknown_game_code_7fd370;
int __fastcall Run_Control_Dialog_006011a0(int,DLGPROC,OwnerDraw::DialogControl *);
long __stdcall Wonline_Selection_Dialog_00752cf0(HWND,unsigned,unsigned,long);
long __stdcall Wonline_Login_Dialog_00752950(HWND,unsigned,unsigned,long);
// @ref ?unknown_game_code_7fd370@@3IA=007fd370
// @ref ?Run_Control_Dialog_006011a0@@YIHHP6GHPAUHWND__@@IIJ@ZPAVDialogControl@OwnerDraw@@@Z=006011a0
// @ref ?Wonline_Selection_Dialog_00752cf0@@YGJPAUHWND__@@IIJ@Z=00752cf0
// @ref ?Wonline_Login_Dialog_00752950@@YGJPAUHWND__@@IIJ@Z=00752950
int Open_Wonline_Selection_00753110()
{
    WolRegistryOptions options;
    options.Read_004ff200();
    unknown_5159b0(0,true);
    if(unknown_ladder_client_a72d00 && strlen(unknown_ladder_address_b29018) && unknown_wstring_b26cb8.Length()>0) {
        unknown_ladder_client_a72d00->Request(unknown_ladder_address_b29018,unknown_ladder_port_b2a8ac,unknown_wstring_b26cb8.Get(),unknown_game_code_7fd370&0xffff00,-1,0,0);
    }
    if(options.unknown_004ff2c0()) {
        SimpleWonlineDialogControl control;
        Run_Control_Dialog_006011a0(0x10e,(DLGPROC)Wonline_Selection_Dialog_00752cf0,&control);
        return unknown_a3d2a4!=0;
    }
    SimpleWonlineDialogControl control;
    Run_Control_Dialog_006011a0(0x11c,(DLGPROC)Wonline_Login_Dialog_00752950,&control);
    return unknown_a3d2a4!=0;
}
