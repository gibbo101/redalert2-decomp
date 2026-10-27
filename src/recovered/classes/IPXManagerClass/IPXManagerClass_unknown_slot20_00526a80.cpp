// int IPXManagerClass::unknown_slot20() (0x00526A80, slot 20)
// The second global channel's queued sends.
#include "shared/ipx_manager.hpp"

int IPXManagerClass::unknown_slot20()
{
    if (!IPXStatus || !Listening || !unknown_4c) {
        return 0;
    }
    return unknown_4c->Queue->SendCount;
}
