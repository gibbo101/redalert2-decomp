// bool IPXAddressClass::operator==(IPXAddressClass &address) (0x005235D0)
// UDP: the IP and the port. IPX: the node, and the network unless either
// network is zero.
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"
// @ref ?IPXProtocol@@3HA=007ddc70

bool IPXAddressClass::operator==(IPXAddressClass &address)
{
    if (IPXProtocol == 2) {
        if (!memcmp(NodeAddress, address.NodeAddress, 4) && !memcmp(NetworkNumber, address.NetworkNumber, 2)) {
            return true;
        }
        return false;
    }
    if ((NetworkNumber[0] == 0 && NetworkNumber[1] == 0 && NetworkNumber[2] == 0 && NetworkNumber[3] == 0)
        || (address.NetworkNumber[0] == 0 && address.NetworkNumber[1] == 0 && address.NetworkNumber[2] == 0
            && address.NetworkNumber[3] == 0)) {
        if (!memcmp(NodeAddress, address.NodeAddress, sizeof(NodeAddress))) {
            return true;
        }
        return false;
    }
    if (!memcmp(NodeAddress, address.NodeAddress, sizeof(NodeAddress))
        && !memcmp(NetworkNumber, address.NetworkNumber, sizeof(NetworkNumber))) {
        return true;
    }
    return false;
}
