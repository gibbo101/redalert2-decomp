// int NullModemClass::Global_Num_Receive() (0x005D1FF0, slot 8)
#include "shared/null_modem.hpp"

int NullModemClass::Global_Num_Receive()
{
    if (Connection) {
        return Connection->Queue->ReceiveCount;
    }
    return 0;
}
