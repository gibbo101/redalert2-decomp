// void IPXAddressClass::Get_Address(NetNumType net, NetNodeType node, unsigned short *socket) (0x005234C0)
// The node, and the network (IPX) or the port (UDP).
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"
// @ref ?IPXProtocol@@3HA=007ddc70

void IPXAddressClass::Get_Address(NetNumType net, NetNodeType node, unsigned short *socket)
{
    memcpy(node, NodeAddress, sizeof(NodeAddress));
    if (IPXProtocol == 1) {
        memcpy(net, NetworkNumber, sizeof(NetworkNumber));
    } else {
        *socket = *(unsigned short *)NetworkNumber;
    }
}
