// int NullModemClass::Private_Num_Receive(int id) (0x005D2030, slot 10)
#include "shared/null_modem.hpp"

int NullModemClass::Private_Num_Receive(int id)
{
    if (Connection) {
        return Connection->Queue->ReceiveCount;
    }
    return 0;
}
