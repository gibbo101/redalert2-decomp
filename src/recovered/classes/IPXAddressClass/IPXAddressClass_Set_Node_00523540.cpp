// void IPXAddressClass::Set_Node(NetNodeType node) (0x00523540)
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"

void IPXAddressClass::Set_Node(NetNodeType node)
{
    memcpy(NodeAddress, node, sizeof(NodeAddress));
}
