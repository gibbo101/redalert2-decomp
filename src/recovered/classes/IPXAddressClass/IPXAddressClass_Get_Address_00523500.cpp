// void IPXAddressClass::Get_Address(NetNumType net, NetNodeType node) (0x00523500)
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"

void IPXAddressClass::Get_Address(NetNumType net, NetNodeType node)
{
    memcpy(node, NodeAddress, sizeof(NodeAddress));
    memcpy(net, NetworkNumber, sizeof(NetworkNumber));
}
