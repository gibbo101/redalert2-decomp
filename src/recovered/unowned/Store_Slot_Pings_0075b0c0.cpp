#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
extern int wol_pending_pings_b292ac[8];
void __fastcall Store_User_Ping_0075b110(char const *name,int ping);
// @ref ?wol_pending_pings_b292ac@@3PAHA=00b292ac
// @ref ?Store_User_Ping_0075b110@@YIXPBDH@Z=0075b110
void Store_Slot_Pings_0075b0c0()
{
    for(int i=0;i<8;++i) {
        if(!unknown_player_slots_a3fa98[i] || !Unknown_005c9320(unknown_player_slots_a3fa98[i])) wol_pending_pings_b292ac[i]=-1;
        // Name is the first member; the original also passes null through the conversion.
        char const *name=Unknown_006FA120((wchar_t const *)unknown_player_slots_a3fa98[i]);
        Store_User_Ping_0075b110(name,wol_pending_pings_b292ac[i]);
    }
}
