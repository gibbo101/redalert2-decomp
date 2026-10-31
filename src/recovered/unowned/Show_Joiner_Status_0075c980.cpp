// @ref ??_C@_0BI@MKML@GUI?3HostGameStartJoiner?$AA@=007e6d78
#include "shared/wol_sink.hpp"
HWND __fastcall Unknown_00735B10();
void __cdecl Unknown_005C2C80(int color,unsigned short const *format,...);
// @ref ?Unknown_00735B10@@YAPAXXZ=00735b10
// @ref ?Unknown_005C2C80@@YAXHPBGZZ=005c2c80
void __fastcall Unknown_0075c980()
{
    HWND dialog=Unknown_00735B10();
    HWND edit=GetDlgItem(dialog,0x59f);
    if(Unknown_0073d3f0((char const *)0)!=1) {
        SendMessageA(edit,0x4dc,0,1);
        Unknown_005C2C80(-1,StringTable::Load_String("GUI:HostGameStartJoiner",0,"D:\\Ra2\\wonline.cpp",0x695e));
    }
}
