// int NullModemClass::Send_Message(void *buf, int buflen, int ack_req) (0x005D05F0)
#include "shared/null_modem.hpp"

int NullModemClass::Send_Message(void *buf, int buflen, int ack_req)
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
