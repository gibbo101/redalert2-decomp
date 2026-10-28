// void NullModemClass::Clear_Receive_Buffer() (0x005D1DA0)
#include "shared/null_modem.hpp"

void NullModemClass::Clear_Receive_Buffer()
{
    ReceiveBuf[0] = 0;
    ReceiveIndex = 0;
}
