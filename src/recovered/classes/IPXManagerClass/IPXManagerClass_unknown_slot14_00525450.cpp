// void IPXManagerClass::unknown_slot14(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout) (0x00525450, slot 14)
// The global channel's timing.
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_slot14(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout)
{
    if (GlobalChannel) {
        GlobalChannel->RetryDelta = retrydelta;
        GlobalChannel->MaxRetries = maxretries;
        GlobalChannel->Timeout = timeout;
    }
}
