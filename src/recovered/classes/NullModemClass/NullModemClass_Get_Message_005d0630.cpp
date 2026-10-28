// int NullModemClass::Get_Message(void *buf, int *buflen) (0x005D0630)
#include "shared/null_modem.hpp"

int NullModemClass::Get_Message(void *buf, int *buflen)
{
    if (!NumConnections) {
        return 0;
    }
    return Connection->Get_Packet(buf, buflen);
}
