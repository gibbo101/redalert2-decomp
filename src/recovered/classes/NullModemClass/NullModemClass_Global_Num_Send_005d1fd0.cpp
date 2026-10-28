// int NullModemClass::Global_Num_Send() (0x005D1FD0, slot 7)
#include "shared/null_modem.hpp"

int NullModemClass::Global_Num_Send()
{
    if (Connection) {
        return Connection->Queue->SendCount;
    }
    return 0;
}
