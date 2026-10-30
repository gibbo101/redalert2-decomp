#include "shared/wol_sink.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
extern char connection_state_debug_007fef4c[];
extern int unknown_connection_pairs_a3fc54[][2];
extern int unknown_connection_states_a3fe54[][2];
extern int unknown_connection_pair_count_a40054;
// @ref ?connection_state_debug_007fef4c@@3PADA=007fef4c
// @ref ?unknown_connection_pairs_a3fc54@@3PAY01HA=00a3fc54
// @ref ?unknown_connection_states_a3fe54@@3PAY01HA=00a3fe54
// @ref ?unknown_connection_pair_count_a40054@@3HA=00a40054
void __fastcall Register_Connection_State_0074e1f0(char const *sender,char const *receiver,int state)
{
    int sender_slot=-1;
    int receiver_slot=-1;
    Debug_Printf(connection_state_debug_007fef4c,sender,receiver,state);
    int i=0;
    for(NodeNameType **slot=unknown_player_slots_a3fa98;(long)slot<(long)(unknown_player_slots_a3fa98+8);++slot,++i) {
        if(_stricmp(Unknown_006FA120((*slot)->Name),sender)==0) sender_slot=i;
        if(_stricmp(Unknown_006FA120((*slot)->Name),receiver)==0) receiver_slot=i;
    }
    for(i=0;i<unknown_connection_pair_count_a40054;++i) {
        if(unknown_connection_pairs_a3fc54[i][0]==sender_slot && unknown_connection_pairs_a3fc54[i][1]==receiver_slot) {
            unknown_connection_states_a3fe54[i][0]=state;
            return;
        }
        if(unknown_connection_pairs_a3fc54[i][0]==receiver_slot && unknown_connection_pairs_a3fc54[i][1]==sender_slot) {
            unknown_connection_states_a3fe54[i][1]=state;
            return;
        }
    }
}
