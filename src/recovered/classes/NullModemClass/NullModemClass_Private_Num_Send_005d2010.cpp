// int NullModemClass::Private_Num_Send(int id) (0x005D2010, slot 9)
#include "shared/null_modem.hpp"

int NullModemClass::Private_Num_Send(int id)
{
    if (Connection) {
        return Connection->Queue->SendCount;
    }
    return 0;
}
