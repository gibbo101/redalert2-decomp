// void UDPInterfaceClass::unknown_slot11(char *address, unsigned short port) (0x0076C290, slot 11)
// Adds a broadcast address given as "a.b.c.d" (the default port when 0).
#include "shared/udp_interface.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref _sscanf=00783730
// @ref ?unknown_default_port_7f60d0@@3HA=007f60d0
// @ref ??_C@_0M@IBML@?$CFd?4?$CFd?4?$CFd?4?$CFd?$AA@=007f1fb4

void UDPInterfaceClass::unknown_slot11(char *address, unsigned short port)
{
    unsigned char *ip = new unsigned char[4];
    int a, b, c, d;
    sscanf(address, "%d.%d.%d.%d", &a, &b, &c, &d);
    ip[0] = a;
    ip[1] = b;
    ip[2] = c;
    ip[3] = d;
    if (port == 0) {
        port = unknown_default_port_7f60d0;
    }
    BroadcastPorts[BroadcastAddresses.Count()] = port;
    BroadcastAddresses.Add(ip);
}
