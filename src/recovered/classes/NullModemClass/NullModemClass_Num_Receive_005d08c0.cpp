// int NullModemClass::Num_Receive() (0x005D08C0)
#include "shared/null_modem.hpp"

int NullModemClass::Num_Receive()
{
    if (Connection) {
        return Connection->Queue->ReceiveCount;
    }
    return 0;
}
