// void IPXManagerClass::unknown_527810(IPXAddressClass *address, unsigned short id) (0x00527810)
// Drops the global channel's unacknowledged sends to an address.
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_527810(IPXAddressClass *address, unsigned short id)
{
    if (GlobalChannel) {
        GlobalChannel->unknown_slot16(address, id);
    }
}
