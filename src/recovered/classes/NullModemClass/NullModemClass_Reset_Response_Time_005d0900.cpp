// void NullModemClass::Reset_Response_Time(bool clear) (0x005D0900, slot 11)
#include "shared/null_modem.hpp"
// @ref ?Reset_Delay@CommBufferClass@@QAEX_N@Z=00480a80

void NullModemClass::Reset_Response_Time(bool clear)
{
    if (Connection) {
        Connection->Queue->Reset_Delay(true);
    }
}
