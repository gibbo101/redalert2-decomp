// IPXAddressClass::IPXAddressClass() (0x00523410)
// The broadcast address (every byte 0xFF).
#include "shared/ipx_address.hpp"

IPXAddressClass::IPXAddressClass()
{
    NetworkNumber[0] = 0xFF;
    NetworkNumber[1] = 0xFF;
    NetworkNumber[2] = 0xFF;
    NetworkNumber[3] = 0xFF;
    NodeAddress[0] = 0xFF;
    NodeAddress[1] = 0xFF;
    NodeAddress[2] = 0xFF;
    NodeAddress[3] = 0xFF;
    NodeAddress[4] = 0xFF;
    NodeAddress[5] = 0xFF;
}
