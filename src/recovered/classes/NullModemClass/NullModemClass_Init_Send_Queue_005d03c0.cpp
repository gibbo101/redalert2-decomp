// int NullModemClass::Init_Send_Queue() (0x005D03C0)
#include "shared/null_modem.hpp"
// @ref ?Init_Send_Queue@CommBufferClass@@QAEXXZ=00480370

int NullModemClass::Init_Send_Queue()
{
    if (Connection) {
        Connection->Queue->Init_Send_Queue();
    }
    return 1;
}
