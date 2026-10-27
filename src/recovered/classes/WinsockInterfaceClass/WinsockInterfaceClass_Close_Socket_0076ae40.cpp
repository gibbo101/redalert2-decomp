// void WinsockInterfaceClass::Close_Socket() (0x0076AE40, slot 1)
#include "shared/winsock_interface.hpp"
// @ref _closesocket@4=00781b96

void WinsockInterfaceClass::Close_Socket()
{
    if (Socket != INVALID_SOCKET) {
        closesocket(Socket);
        Socket = INVALID_SOCKET;
    }
    if (Socket2 != INVALID_SOCKET) {
        closesocket(Socket2);
        Socket2 = INVALID_SOCKET;
    }
}
