// void NullModemClass::unknown_slot14(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout) (0x005D1F40, slot 14)
#include "shared/null_modem.hpp"

void NullModemClass::unknown_slot14(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout)
{
    Set_Timing(retrydelta, maxretries, timeout, true);
}
