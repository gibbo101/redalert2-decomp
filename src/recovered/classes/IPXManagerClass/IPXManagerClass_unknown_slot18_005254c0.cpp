// void IPXManagerClass::unknown_slot18(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout) (0x005254C0, slot 18)
// The second global channel's and the multicast connection's timing.
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_slot18(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout)
{
    if (unknown_4c) {
        unknown_4c->RetryDelta = retrydelta;
        unknown_4c->MaxRetries = maxretries;
        unknown_4c->Timeout = timeout;
    }
    if (unknown_50) {
        unknown_50->RetryDelta = retrydelta;
        unknown_50->MaxRetries = maxretries;
        unknown_50->Timeout = timeout;
    }
}
