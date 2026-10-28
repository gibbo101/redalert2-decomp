// void IPXAddressClass::Set_Protocol(int protocol) (0x00523950)
// 1 IPX, 2 UDP.
#include "shared/ipx_address.hpp"
// @ref ?IPXProtocol@@3HA=007ddc70

void __fastcall IPXAddressClass::Set_Protocol(int protocol)
{
    IPXProtocol = protocol;
}
