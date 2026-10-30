#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/options.hpp"
#include "shared/string_table.hpp"
bool __fastcall Can_Join_Channel_00755cd0(WOL::Channel const *,bool,bool);
bool __fastcall Test_Display_Mode(int width,int height);
int __fastcall Run_Control_Dialog_006011a0(int,DLGPROC,OwnerDraw::DialogControl *);
long __stdcall Wonline_Password_Dialog_007492d0(HWND,unsigned,unsigned,long);
int __fastcall Join_Channel_00744700(WOL::Channel const *,Wstring const &,WideString);
extern bool connection_wait_callback_0073c120();
extern char wol_source_file_007fd62c[];
extern char wol_screen_800_label_7fe8b8[],wol_screen_limit_label_7fe89c[],wol_joining_label_7fe688[];
extern char wol_password_find_7e613c[],wol_password_replace_7cf730[];
// @ref ?Can_Join_Channel_00755cd0@@YI_NPBUChannel@WOL@@_N1@Z=00755cd0
// @ref ?Test_Display_Mode@@YI_NHH@Z=00543a70
// @ref ?Replace@Wstring@@QAE_NPBD0@Z=0076ea90
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?Save_Settings@OptionsClass@@QAEXXZ=005d91b0
// @ref ?Run_Control_Dialog_006011a0@@YIHHP6GHPAUHWND__@@IIJ@ZPAVDialogControl@OwnerDraw@@@Z=006011a0
// @ref ?Wonline_Password_Dialog_007492d0@@YGJPAUHWND__@@IIJ@Z=007492d0
// @ref ?Join_Channel_00744700@@YIHPBUChannel@WOL@@ABVWstring@@VWideString@@@Z=00744700
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_screen_800_label_7fe8b8@@3PADA=007fe8b8
// @ref ?wol_screen_limit_label_7fe89c@@3PADA=007fe89c
// @ref ?wol_joining_label_7fe688@@3PADA=007fe688
// @ref ?wol_password_find_7e613c@@3PADA=007e613c
// @ref ?wol_password_replace_7cf730@@3PADA=007cf730
bool __fastcall Join_Game_Channel_00745780(WOL::Channel const *channel,bool observer)
{
    if(!Can_Join_Channel_00755cd0(channel,true,observer)) return false;
    unsigned int mode=channel->unknown_20;
    int maximum=(mode&0x400)?800:((mode&0x200)?640:1024);
    if(unknown_8523e0>maximum) {
        {
            WideString warning((mode&0x400)?
                StringTable::Load_String(wol_screen_800_label_7fe8b8,0,wol_source_file_007fd62c,0x279f):
                StringTable::Load_String(wol_screen_limit_label_7fe89c,0,wol_source_file_007fd62c,0x27a0));
            if(Message_Box_005c3230(warning.Get(),4,connection_wait_callback_0073c120,true)==6) {
                int width=(maximum==800)?800:640;
                int height=(width==800)?600:480;
                if(Test_Display_Mode(width,height)) {
                    Options.ScreenWidth=width;
                    Options.ScreenHeight=height;
                    Options.Save_Settings();
                }
            }
        }
        if(unknown_8523e0>maximum) return false;
    }
    Wstring password;
    // The external WOL channel flags occupy the second DWORD of this still-flat field.
    if(*(unsigned int const *)(channel->unknown_18+4)&0x100) {
        unknown_5159b0(0,true);
        WonlineStringDialogControl control;
        if(Run_Control_Dialog_006011a0(0xe1,(DLGPROC)Wonline_Password_Dialog_007492d0,&control)==2) return false;
        password=control.Text;
        password.Replace(wol_password_find_7e613c,wol_password_replace_7cf730);
    }
    return Join_Channel_00744700(channel,password,StringTable::Load_String(wol_joining_label_7fe688,0,wol_source_file_007fd62c,0x27d7))==0;
}
