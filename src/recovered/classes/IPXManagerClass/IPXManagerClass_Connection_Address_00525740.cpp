// IPXAddressClass *IPXManagerClass::Connection_Address(int id) (0x00525740)
#include "shared/ipx_manager.hpp"

IPXAddressClass *IPXManagerClass::Connection_Address(int id)
{
    for (int i = 0; i < NumConnections; i++) {
        if (Connection[i]->ID == id) {
            return &Connection[i]->Address;
        }
    }
    return 0;
}
