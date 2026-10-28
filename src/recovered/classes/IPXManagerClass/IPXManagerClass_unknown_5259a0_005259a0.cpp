// int IPXManagerClass::unknown_5259a0(void *buf, int buflen, int ack_req, wchar_t const *name) (0x005259A0)
// Sends a global message to another session node chosen by name (never the
// first node, this player).
#include "shared/ipx_manager.hpp"
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_node_ids_a402ba@@3PAGA=00a402ba
// @ref __wcsicmp=00796318

int IPXManagerClass::unknown_5259a0(void *buf, int buflen, int ack_req, wchar_t const *name)
{
    if (unknown_players_a3fa7c.Count() && !_wcsicmp(unknown_players_a3fa7c[0]->Name, name)) {
        return 0;
    }
    for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
        if (!_wcsicmp(unknown_players_a3fa7c[i]->Name, name)) {
            IPXAddressClass address = unknown_players_a3fa7c[i]->Address;
            return Send_Global_Message(buf, buflen, ack_req, &address, unknown_node_ids_a402ba[i], 0);
        }
    }
    return 0;
}
