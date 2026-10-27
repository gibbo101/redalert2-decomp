// void UDPInterfaceClass::unknown_slot30(unsigned long *address, unsigned short port) (0x0076CBC0, slot 30)
// Remembers an address and port as unreachable (up to 16).
#include "shared/udp_interface.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0DB@OJNJ@Marking?5address?5?$CFd?4?$CFd?4?$CFd?4?$CFd?5?$DL?5?$CFd@=00801118

void UDPInterfaceClass::unknown_slot30(unsigned long *address, unsigned short port)
{
    if (NumUnreachable >= 16) {
        return;
    }
    for (int i = 0; i < NumUnreachable; i++) {
        if (port == UnreachablePorts[i] && *address == UnreachableAddresses[i]) {
            return;
        }
    }
    Debug_Printf("Marking address %d.%d.%d.%d ; %d as unreachable\n",
        ((unsigned char *)address)[0], ((unsigned char *)address)[1],
        ((unsigned char *)address)[2], ((unsigned char *)address)[3], port);
    UnreachableAddresses[NumUnreachable] = *address;
    UnreachablePorts[NumUnreachable] = port;
    NumUnreachable++;
}
