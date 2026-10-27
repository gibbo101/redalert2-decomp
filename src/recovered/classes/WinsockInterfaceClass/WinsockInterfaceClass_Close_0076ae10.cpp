// void WinsockInterfaceClass::Close() (0x0076AE10)
// Stops listening, closes the sockets and shuts Winsock down.
#include "shared/winsock_interface.hpp"
// @ref _WSACleanup@0=00781bba

void WinsockInterfaceClass::Close()
{
    if (WinsockInitialised) {
        Stop_Listening();
        Close_Socket();
        WSACleanup();
        WinsockInitialised = false;
    }
}
