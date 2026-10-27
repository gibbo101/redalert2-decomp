// int IPXManagerClass::unknown_5258b0(void *buf, int buflen, int ack_req, int node_id) (0x005258B0)
// Sends a global message to another session node chosen by ID (never the
// first node, this player).
#include "shared/ipx_manager.hpp"
// @ref ?unknown_nodes_a3fa7c@@3V?$DynamicVectorClass@PAUUnknownNodeName@@@@A=00a3fa7c
// @ref ?unknown_node_ids_a402ba@@3PAGA=00a402ba

int IPXManagerClass::unknown_5258b0(void *buf, int buflen, int ack_req, int node_id)
{
    if (unknown_nodes_a3fa7c.Count() && unknown_nodes_a3fa7c[0]->ID == node_id) {
        return 0;
    }
    for (int i = 1; i < unknown_nodes_a3fa7c.Count(); i++) {
        if (unknown_nodes_a3fa7c[i]->ID == node_id) {
            IPXAddressClass address = unknown_nodes_a3fa7c[i]->Address;
            return Send_Global_Message(buf, buflen, ack_req, &address, unknown_node_ids_a402ba[i], 0);
        }
    }
    return 0;
}
