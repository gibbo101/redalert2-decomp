// IPXAddressClass::IPXAddressClass(NetNumType net, NetNodeType node, unsigned short socket) (0x00523440)
// The node, and the network (IPX) or the port in the first word (UDP).
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"
// @ref ?IPXProtocol@@3HA=007ddc70

IPXAddressClass::IPXAddressClass(NetNumType net, NetNodeType node, unsigned short socket)
{
    memcpy(NodeAddress, node, sizeof(NodeAddress));
    if (IPXProtocol == 1) {
        memcpy(NetworkNumber, net, sizeof(NetworkNumber));
    } else {
        memset(NetworkNumber, 0, sizeof(NetworkNumber));
        *(unsigned short *)NetworkNumber = socket;
    }
}
