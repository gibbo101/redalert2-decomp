// void IPXAddressClass::Get_Node(NetNodeType node) (0x00523520)
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"

void IPXAddressClass::Get_Node(NetNodeType node)
{
    memcpy(node, NodeAddress, sizeof(NodeAddress));
}
