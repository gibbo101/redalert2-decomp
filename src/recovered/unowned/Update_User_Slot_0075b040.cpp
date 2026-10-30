#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
void __fastcall Unknown_004d1060(HWND dialog,int slot,int value);
// @ref ?Unknown_004d1060@@YIXPAUHWND__@@HH@Z=004d1060
// @ref ?Find_Lobby_Window_005c2c40@@YAPAUHWND__@@XZ=005c2c40
void __fastcall Update_User_Slot_0075b040(WOL::User const *user)
{
    if(user) {
        for(int i=0;i<8;++i) {
            if(unknown_player_slots_a3fa98[i] && !strcmp(Unknown_006FA120((wchar_t const *)unknown_player_slots_a3fa98[i]),user->name)) {
                HWND dialog=Find_Lobby_Window_005c2c40();
                if(dialog) Unknown_004d1060(dialog,i,-1);
                return;
            }
        }
    }
}
