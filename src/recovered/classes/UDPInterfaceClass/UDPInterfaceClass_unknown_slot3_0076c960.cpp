// void UDPInterfaceClass::unknown_slot3(void *buf, int buflen, void *address, int addresslen, bool alternate, unsigned char arg6, unsigned short arg7) (0x0076C960, slot 3)
// A write to a broadcast address becomes a broadcast.
#include "shared/udp_interface.hpp"
// @ref ?Is_Broadcast@IPXAddressClass@@QAEHXZ=00523560
// @ref ?unknown_slot3@WinsockInterfaceClass@@UAEXPAXH0H_NEG@Z=0076b670

void UDPInterfaceClass::unknown_slot3(void *buf, int buflen, void *address, int addresslen, bool alternate, unsigned char arg6, unsigned short arg7)
{
    if (address && ((IPXAddressClass *)address)->Is_Broadcast()) {
        unknown_slot4(buf, buflen, alternate);
        return;
    }
    WinsockInterfaceClass::unknown_slot3(buf, buflen, address, addresslen, alternate, arg6, arg7);
}
