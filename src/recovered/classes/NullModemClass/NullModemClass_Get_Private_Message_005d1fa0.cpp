// int NullModemClass::Get_Private_Message(void *buf, int *buflen, int *conn_id) (0x005D1FA0, slot 3)
#include "shared/null_modem.hpp"

int NullModemClass::Get_Private_Message(void *buf, int *buflen, int *conn_id)
{
    if (!NumConnections) {
        return 0;
    }
    return Connection->Get_Packet(buf, buflen);
}
