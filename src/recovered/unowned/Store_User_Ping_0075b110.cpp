#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_string.hpp"
extern int wol_player_pings_b292ac[8];
extern char wol_store_ping_debug_007fff54[];
// @ref ?wol_player_pings_b292ac@@3PAHA=00b292ac
// @ref ?wol_store_ping_debug_007fff54@@3PADA=007fff54
void __fastcall Store_User_Ping_0075b110(char const *name,int ping)
{
    Debug_Printf(wol_store_ping_debug_007fff54,name,ping);
    for(int i=0;i<8;++i) {
        if(unknown_player_slots_a3fa98[i] && !strcmp(Unknown_006FA120(unknown_player_slots_a3fa98[i]->Name),name)) {
            wol_player_pings_b292ac[i]=ping;
            HWND dialog=Find_Lobby_Window_005c2c40();
            if(dialog) {
                if(ping<0) Set_Player_Ping_4d1060(dialog,i,-1);
                else if(ping<300) Set_Player_Ping_4d1060(dialog,i,0);
                else if(ping<500) Set_Player_Ping_4d1060(dialog,i,1);
                else Set_Player_Ping_4d1060(dialog,i,2);
            }
        }
    }
}
