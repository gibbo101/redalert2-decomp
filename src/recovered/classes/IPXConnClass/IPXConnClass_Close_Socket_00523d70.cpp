// void IPXConnClass::Close_Socket() (0x00523D70)
#include "shared/ipx_conn.hpp"
// @ref ?SocketOpen@IPXConnClass@@2HA=00a52408
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50

void IPXConnClass::Close_Socket()
{
    PacketTransport->Close_Socket();
    SocketOpen = 0;
}
