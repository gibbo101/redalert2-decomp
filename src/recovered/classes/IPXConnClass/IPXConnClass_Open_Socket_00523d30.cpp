// void __fastcall IPXConnClass::Open_Socket(unsigned short socket) (0x00523D30)
#include "shared/ipx_conn.hpp"
// @ref ?SocketOpen@IPXConnClass@@2HA=00a52408
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50
// @ref ?unknown_a40b60@@3HA=00a40b60

void __fastcall IPXConnClass::Open_Socket(unsigned short socket)
{
    PacketTransport->unknown_slot20(unknown_a40b60);
    SocketOpen = PacketTransport->unknown_slot15(socket);
}
