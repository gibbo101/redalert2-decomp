// void IPXManagerClass::unknown_slot16() (0x00525480, slot 16)
// Saves the global channel's timing.
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_slot16()
{
    if (GlobalChannel) {
        unknown_64 = GlobalChannel->RetryDelta;
        unknown_68 = GlobalChannel->MaxRetries;
        unknown_6c = GlobalChannel->Timeout;
    }
}
