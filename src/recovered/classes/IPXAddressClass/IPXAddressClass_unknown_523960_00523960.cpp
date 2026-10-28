// void IPXAddressClass::unknown_523960(unsigned short port) (0x00523960)
// UDP only: the port in the first word.
#include "shared/ipx_address.hpp"
// @ref ?IPXProtocol@@3HA=007ddc70

void IPXAddressClass::unknown_523960(unsigned short port)
{
    if (IPXProtocol == 2) {
        *(unsigned short *)NetworkNumber = port;
    }
}
