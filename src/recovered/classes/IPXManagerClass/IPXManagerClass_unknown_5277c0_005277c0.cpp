// void IPXManagerClass::unknown_5277c0(IPXAddressClass *address) (0x005277C0)
// The second global channel's address.
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_5277c0(IPXAddressClass *address)
{
    if (unknown_4c) {
        unknown_4c->Address = *address;
    }
}
