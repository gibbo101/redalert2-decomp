// Original callers pass a zero low-byte register argument. Its boolean source type
// is a hypothesis: this body never reads the argument, so signedness is unobservable.
// @ref ??_C@_0M@CHOE@TXT_JOINLOB?$AA@=007fe688
#include "shared/wol_sink.hpp"
int Unknown_00744090();
void __fastcall Refresh_Game_List_0073f8f0();
int __fastcall Unknown_00744700(WOL::Channel const &channel, Wstring const &password, WideString title);
// @ref ?Unknown_00744090@@YAHXZ=00744090
// @ref ?Unknown_00744700@@YIHABUChannel@WOL@@ABVWstring@@VWideString@@@Z=00744700
// @ref ??_C@_08EIMP@zotclot9?$AA@=007fe738
int __fastcall Join_Selected_Lobby_00744930(bool unknown)
{
    int choice=Unknown_00744090();
    if(choice!=-1) {
        WOL::Channel channel;
        unknown_lobbies_b26c88.Get(channel,choice);
        int result;
        {
        Wstring password("zotclot9");
        result=Unknown_00744700(channel,password,StringTable::Load_String("TXT_JOINLOB",0,"D:\\Ra2\\wonline.cpp",0x24d4));
        }
        if(!result) {
            HWND dialog=(HWND)Unknown_00735940(0x113);
            if(dialog) SetFocus(GetDlgItem(dialog,0x540));
            Refresh_Game_List_0073f8f0();
            return choice;
        }
    }
    Refresh_Game_List_0073f8f0();
    return -1;
}
