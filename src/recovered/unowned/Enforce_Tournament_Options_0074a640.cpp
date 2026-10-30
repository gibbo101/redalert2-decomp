#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
void __fastcall Enforce_Tournament_Options_0074a640(HWND dialog)
{
    if(Unknown_0073c340(&unknown_game_channel_b299c0)) {
        EnableWindow(GetDlgItem(dialog,0x552),false);
        EnableWindow(GetDlgItem(dialog,0x553),false);
        EnableWindow(GetDlgItem(dialog,0x597),false);
        unknown_session_a3d298.AICount=0;
        unknown_session_a3d298.unknown_a4=false;
        HWND first=GetDlgItem(dialog,0x54e);
        SendMessageA(first,0xf1,1,0);
        EnableWindow(first,false);
        HWND second=GetDlgItem(dialog,0x54b);
        SendMessageA(second,0xf1,1,0);
        EnableWindow(second,false);
        unknown_session_a3d298.unknown_2a=true;
        unknown_session_a3d298.unknown_bases_20=true;
    }
}
