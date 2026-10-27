// void WinsockInterfaceClass::Clear_Socket_Error(SOCKET socket) (0x0076B8A0, slot 9)
// Reads and then clears the socket's pending error.
#include "shared/winsock_interface.hpp"
// @ref _getsockopt@20=00781b90
// @ref _setsockopt@20=00781ba8

void WinsockInterfaceClass::Clear_Socket_Error(SOCKET socket)
{
    unsigned long error_code;
    int length = 4;
    getsockopt(socket, 0xFFFF, 0x1007, (char *)&error_code, &length);
    error_code = 0;
    setsockopt(socket, 0xFFFF, 0x1007, (char *)&error_code, length);
}
