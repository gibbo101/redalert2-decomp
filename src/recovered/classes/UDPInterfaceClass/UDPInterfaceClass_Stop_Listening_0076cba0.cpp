// void UDPInterfaceClass::Stop_Listening() (0x0076CBA0, slot 8)
#include "shared/udp_interface.hpp"
// @ref ?Stop_Listening@WinsockInterfaceClass@@UAEXXZ=0076af10

void UDPInterfaceClass::Stop_Listening()
{
    WinsockInterfaceClass::Stop_Listening();
    unknown_slot28();
}
