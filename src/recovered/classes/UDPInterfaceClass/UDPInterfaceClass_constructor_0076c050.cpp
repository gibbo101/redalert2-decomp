// UDPInterfaceClass::UDPInterfaceClass() (0x0076C050)
#include "shared/udp_interface.hpp"
// @ref ??0WinsockInterfaceClass@@QAE@XZ=0076ac80
// @ref ??_7UDPInterfaceClass@@6B@=007afb2c
// @ref ??_7?$DynamicVectorClass@PAE@@6B@=007afbac

UDPInterfaceClass::UDPInterfaceClass()
{
    unknown_3f2fc = 0;
    NumSockets = 0;
    NumUnreachable = 0;
    unknown_3f334 = INVALID_SOCKET;
}
