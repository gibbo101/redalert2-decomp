#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern unsigned short unknown_player_ports_a40058[8];
extern char player_port_message_7fe030[];
// @ref ?unknown_player_ports_a40058@@3PAGA=00a40058
// @ref ?player_port_message_7fe030@@3PADA=007fe030
void __fastcall Store_Player_Port_0074e2d0(char const *name,unsigned short port)
{
    Debug_Printf(player_port_message_7fe030,name,port);
    for(int i=0;i<8;++i) {
        if(!_stricmp(Unknown_006FA120((wchar_t const *)unknown_player_slots_a3fa98[i]),name)) {
            unknown_player_ports_a40058[i]=port;
            return;
        }
    }
}
