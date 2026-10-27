// WinsockInterfaceClass::~WinsockInterfaceClass() (0x0076AD70)
#include "shared/winsock_interface.hpp"
// @ref ??_7?$VectorClass@PAVWinsockBufferType@WinsockInterfaceClass@@@@6B@=007afafc
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _WSACleanup@0=00781bba

WinsockInterfaceClass::~WinsockInterfaceClass()
{
    Close();
}
