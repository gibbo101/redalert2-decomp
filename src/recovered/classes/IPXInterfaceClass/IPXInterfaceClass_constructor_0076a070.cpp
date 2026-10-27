// IPXInterfaceClass::IPXInterfaceClass() (0x0076A070)
// The network and node addresses start unknown (all 0xFF).
#include "shared/ipx_interface.hpp"
// @ref ??0WinsockInterfaceClass@@QAE@XZ=0076ac80
// @ref ??_7IPXInterfaceClass@@6B@=007afa0c

IPXInterfaceClass::IPXInterfaceClass()
{
    memset(Network, 0xFF, sizeof(Network));
    memset(Node, 0xFF, sizeof(Node));
    memset(unknown_3f306, 0xFF, sizeof(unknown_3f306));
}
