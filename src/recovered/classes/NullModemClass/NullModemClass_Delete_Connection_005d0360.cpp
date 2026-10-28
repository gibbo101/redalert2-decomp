// int NullModemClass::Delete_Connection() (0x005D0360)
// Deletes the connection and the buffers.
#include "shared/null_modem.hpp"

int NullModemClass::Delete_Connection()
{
    if (Connection) {
        delete Connection;
        Connection = 0;
    }
    if (SendBuf) {
        delete SendBuf;
        SendBuf = 0;
    }
    if (BuildBuf) {
        delete BuildBuf;
        BuildBuf = 0;
    }
    if (ReceiveBuf) {
        delete ReceiveBuf;
        ReceiveBuf = 0;
    }
    NumConnections = 0;
    return 1;
}
