#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/win32_window.hpp"
long __stdcall Wonline_Wait_Dialog_0074d5e0(HWND window,unsigned message,unsigned wparam,long lparam);
extern bool connection_wait_callback_0073c120();
// @ref ?Wonline_Wait_Dialog_0074d5e0@@YGJPAUHWND__@@IIJ@Z=0074d5e0
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
// @ref ?ProgramInstance@@3PAXA=00b26180
void __fastcall Open_Wait_Window_0074d4d0(unsigned int events,WideString const &message,bool block)
{
    HWND dialog=Find_Dialog_00735940(0xc4);
    if(dialog) {
        unknown_b2abe0 |= events;
        if(message.Length()>0) {
            HWND text=GetDlgItem(dialog,0x5b2);
            SendMessageA(text,0x4b2,0,(LPARAM)message.unknown_text_770430());
        }
    } else if(events) {
        HWND focus=Unknown_00735B10();
        focus=GetDlgItem(focus,0x540);
        dialog=(HWND)unknown_create_dialog_735700(ProgramInstance,0xc4,MainWindow,Wonline_Wait_Dialog_0074d5e0,0);
        unknown_show_dialog_5ff7e0(dialog,0xc4);
        HWND text=GetDlgItem(dialog,0x5b2);
        SendMessageA(text,0x4b2,0,(LPARAM)message.unknown_text_770430());
        unknown_b2abe0=events;
        if(focus) SetFocus(focus);
    }
    if(block && unknown_b2abe0) Unknown_007359e0(dialog,connection_wait_callback_0073c120,0,1,0);
}
