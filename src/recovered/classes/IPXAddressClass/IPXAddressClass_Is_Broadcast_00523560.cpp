// int IPXAddressClass::Is_Broadcast() (0x00523560)
// Every byte 0xFF (IPX), or every node byte (UDP).
#include "shared/ipx_address.hpp"
// @ref ?IPXProtocol@@3HA=007ddc70

int IPXAddressClass::Is_Broadcast()
{
    if (IPXProtocol == 1) {
        if (NetworkNumber[0] != 0xFF || NetworkNumber[1] != 0xFF || NetworkNumber[2] != 0xFF || NetworkNumber[3] != 0xFF
            || NodeAddress[0] != 0xFF || NodeAddress[1] != 0xFF || NodeAddress[2] != 0xFF || NodeAddress[3] != 0xFF || NodeAddress[4] != 0xFF || NodeAddress[5] != 0xFF) {
            return 0;
        }
        return 1;
    }
    if (NodeAddress[0] != 0xFF || NodeAddress[1] != 0xFF || NodeAddress[2] != 0xFF || NodeAddress[3] != 0xFF || NodeAddress[4] != 0xFF || NodeAddress[5] != 0xFF) {
        return 0;
    }
    return 1;
}
