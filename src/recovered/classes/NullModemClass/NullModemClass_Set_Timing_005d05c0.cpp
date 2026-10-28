// void NullModemClass::Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout, bool global) (0x005D05C0, slot 13)
#include "shared/null_modem.hpp"

void NullModemClass::Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout, bool global)
{
    RetryDelta = retrydelta;
    MaxRetries = maxretries;
    Timeout = timeout;
    Connection->RetryDelta = RetryDelta;
    Connection->MaxRetries = MaxRetries;
    Connection->Timeout = Timeout;
}
