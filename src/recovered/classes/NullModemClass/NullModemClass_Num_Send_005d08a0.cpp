// int NullModemClass::Num_Send() (0x005D08A0)
#include "shared/null_modem.hpp"

int NullModemClass::Num_Send()
{
    if (Connection) {
        return Connection->Queue->SendCount;
    }
    return 0;
}
