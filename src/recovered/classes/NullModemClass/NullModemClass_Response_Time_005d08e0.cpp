// unsigned long NullModemClass::Response_Time() (0x005D08E0, slot 12)
#include "shared/null_modem.hpp"
// @ref ?Avg_Delay@CommBufferClass@@QAEKXZ=00480a60

unsigned long NullModemClass::Response_Time()
{
    if (Connection) {
        return Connection->Queue->Avg_Delay();
    }
    return 0;
}
