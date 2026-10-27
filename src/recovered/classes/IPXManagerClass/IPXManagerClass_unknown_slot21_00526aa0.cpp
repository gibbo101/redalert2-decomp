// int IPXManagerClass::unknown_slot21() (0x00526AA0, slot 21)
// The second global channel's queued receives.
#include "shared/ipx_manager.hpp"

int IPXManagerClass::unknown_slot21()
{
    if (!IPXStatus || !Listening || !unknown_4c) {
        return 0;
    }
    return unknown_4c->Queue->ReceiveCount;
}
