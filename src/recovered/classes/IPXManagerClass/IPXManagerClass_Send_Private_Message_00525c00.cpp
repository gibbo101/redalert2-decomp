// int IPXManagerClass::Send_Private_Message(void *buf, int buflen, int ack_req, int conn_id) (0x00525C00, slot 2)
// Sends to one connection, or to all (through the multicast connection
// when forwarding); refuses, counting an overflow, when a queue is full.
#include "shared/ipx_manager.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_flag_a3fba8@@3_NA=00a3fba8

int IPXManagerClass::Send_Private_Message(void *buf, int buflen, int ack_req, int conn_id)
{
    int i;
    if (!IPXStatus || !Listening || NumConnections == 0) {
        return 0;
    }
    if (conn_id == -1) {
        if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8) {
            if (unknown_50->Queue->SendCount >= unknown_50->Queue->MaxSend) {
                SendOverflows++;
                return 0;
            }
            return unknown_50->Send_Packet(buf, buflen, ack_req, 0xFF);
        }
        for (i = 0; i < NumConnections; i++) {
            if (Connection[i]->Queue->SendCount == Connection[i]->Queue->MaxSend) {
                SendOverflows++;
                return 0;
            }
        }
        for (i = 0; i < NumConnections; i++) {
            Connection[i]->Send_Packet(buf, buflen, ack_req, 0);
        }
        return 1;
    }
    int index = Connection_Index(conn_id);
    if (index == -1 || Connection[index]->Queue->SendCount == Connection[index]->Queue->MaxSend) {
        SendOverflows++;
        return 0;
    }
    Connection[index]->Send_Packet(buf, buflen, ack_req, 0);
    return 1;
}
