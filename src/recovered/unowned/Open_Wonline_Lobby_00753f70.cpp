#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/wonline_dialog_control.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
extern unsigned int unknown_game_code_7fd370;
extern char wol_source_file_007fd62c[];
extern char wol_wait_label_7fe670[];
int __fastcall Unknown_00742390();
void __fastcall Open_Wait_Window_0074d4d0(unsigned int,WideString const &,bool);
int __fastcall Unknown_00751c30(unsigned int flags);
int __fastcall Run_Control_Dialog_006011a0(int,DLGPROC,OwnerDraw::DialogControl *);
long __stdcall Wonline_Lobby_Dialog_00753370(HWND,unsigned,unsigned,long);
// @ref ?unknown_game_code_7fd370@@3IA=007fd370
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_wait_label_7fe670@@3PADA=007fe670
// @ref ?Unknown_00742390@@YIHXZ=00742390
// @ref ?Open_Wait_Window_0074d4d0@@YIXIABVWideString@@_N@Z=0074d4d0
// @ref ?Unknown_00751c30@@YIHI@Z=00751c30
// @ref ?Run_Control_Dialog_006011a0@@YIHHP6GHPAUHWND__@@IIJ@ZPAVDialogControl@OwnerDraw@@@Z=006011a0
// @ref ?Wonline_Lobby_Dialog_00753370@@YGJPAUHWND__@@IIJ@Z=00753370
int __fastcall Open_Wonline_Lobby_00753f70()
{
    int initialized=Unknown_00742390();
    if(initialized==1) {
        {
            WideString message(StringTable::Load_String(wol_wait_label_7fe670,0,wol_source_file_007fd62c,0x56cc));
            Open_Wait_Window_0074d4d0(0x10,message,false);
        }
        unsigned int flags=0x2300;
        if(unknown_a3d2a4!=2) flags=0x2100;
        int result=Unknown_00751c30(flags);
        switch(result) {
        case 0: break;
        case 2: return -1;
        default: return -2;
        }
        if(unknown_ladder_client_a72d00 && strlen(unknown_ladder_address_b29018) && unknown_wstring_b26cb8.Length()>0) {
            unknown_ladder_client_a72d00->Request(unknown_ladder_address_b29018,unknown_ladder_port_b2a8ac,unknown_wstring_b26cb8.Get(),unknown_game_code_7fd370&0xffff00,-1,0,0);
        }
        SimpleWonlineDialogControl control;
        Run_Control_Dialog_006011a0(0x114,(DLGPROC)Wonline_Lobby_Dialog_00753370,&control);
        return unknown_a3d2a4!=0;
    }
    return initialized;
}
