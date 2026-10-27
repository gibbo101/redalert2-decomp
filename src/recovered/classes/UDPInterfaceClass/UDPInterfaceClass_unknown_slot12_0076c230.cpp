// void UDPInterfaceClass::unknown_slot12() (0x0076C230, slot 12)
// Frees the broadcast addresses.
#include "shared/udp_interface.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void UDPInterfaceClass::unknown_slot12()
{
    while (BroadcastAddresses.Count()) {
        delete BroadcastAddresses[0];
        BroadcastAddresses.Delete(0);
    }
}
