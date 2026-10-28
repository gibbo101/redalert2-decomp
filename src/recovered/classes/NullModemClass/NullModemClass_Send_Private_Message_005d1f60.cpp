// int NullModemClass::Send_Private_Message(void *buf, int buflen, int ack_req, int conn_id) (0x005D1F60, slot 2)
#include "shared/null_modem.hpp"

int NullModemClass::Send_Private_Message(void *buf, int buflen, int ack_req, int conn_id)
{
    if (!NumConnections) {
        return 0;
    }
    int result = Connection->Send_Packet(buf, buflen, ack_req, 0);
    if (!result) {
        SendOverflows++;
    }
    return result;
}
