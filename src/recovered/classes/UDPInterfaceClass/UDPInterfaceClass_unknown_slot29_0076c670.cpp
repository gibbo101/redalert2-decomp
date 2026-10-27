// void UDPInterfaceClass::unknown_slot29(unsigned short port) (0x0076C670, slot 29)
// Selects the socket bound to a non-default port (else none).
#include "shared/udp_interface.hpp"
// @ref ?unknown_default_port_7f60d0@@3HA=007f60d0

void UDPInterfaceClass::unknown_slot29(unsigned short port)
{
    if (port && port != unknown_default_port_7f60d0) {
        for (int i = 0; i < NumSockets; i++) {
            if (SocketPorts[i] == port) {
                unknown_3f334 = Sockets[i];
                return;
            }
        }
    }
    unknown_3f334 = INVALID_SOCKET;
}
