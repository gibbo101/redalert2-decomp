// void IPXManagerClass::unknown_slot17() (0x005254A0, slot 17)
// Restores the global channel's saved timing.
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_slot17()
{
    if (GlobalChannel) {
        GlobalChannel->RetryDelta = unknown_64;
        GlobalChannel->MaxRetries = unknown_68;
        GlobalChannel->Timeout = unknown_6c;
    }
}
