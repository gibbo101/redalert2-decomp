// UDPInterfaceClass::~UDPInterfaceClass() (0x0076C0F0)
// Frees the broadcast and local addresses, then shuts Winsock down.
#include "shared/udp_interface.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Close@WinsockInterfaceClass@@QAEXXZ=0076ae10
// @ref ??1WinsockInterfaceClass@@UAE@XZ=0076ad70
// @ref ??_7?$VectorClass@PAE@@6B@=007afbcc

UDPInterfaceClass::~UDPInterfaceClass()
{
    unknown_slot12();
    while (LocalAddresses.Count()) {
        delete LocalAddresses[0];
        LocalAddresses.Delete(0);
    }
    Close();
}
