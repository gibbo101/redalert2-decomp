// unsigned int UDPInterfaceClass::unknown_slot14(int socket) (0x0076D3F0, slot 14)
// The notification message: 0x474 for the primary socket (or -1), 0x475
// for the alternate, else 0.
#include "shared/udp_interface.hpp"

unsigned int UDPInterfaceClass::unknown_slot14(int socket)
{
    if (socket == (int)Socket || socket == -1) {
        return 0x474;
    }
    return socket == (int)Socket2 ? 0x475 : 0;
}
