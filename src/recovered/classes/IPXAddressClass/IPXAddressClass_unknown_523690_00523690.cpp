// bool IPXAddressClass::unknown_523690(IPXAddressClass &address) (0x00523690)
// The node only: the IP (4 bytes) under UDP, else all six.
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"
// @ref ?IPXProtocol@@3HA=007ddc70

bool IPXAddressClass::unknown_523690(IPXAddressClass &address)
{
    return memcmp(NodeAddress, address.NodeAddress, IPXProtocol == 2 ? 4 : 6) == 0;
}
