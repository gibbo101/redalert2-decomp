// void WinsockInterfaceClass::Stop_Listening() (0x0076AF10, slot 8)
#include "shared/winsock_interface.hpp"
// @ref _WSAAsyncSelect@16=00781bc0
// @ref ?unknown_window_b263d8@@3PAXA=00b263d8

void WinsockInterfaceClass::Stop_Listening()
{
    if (Socket != INVALID_SOCKET && unknown_window_b263d8) {
        WSAAsyncSelect(Socket, unknown_window_b263d8, 0, 0);
    }
    if (Socket2 != INVALID_SOCKET && unknown_window_b263d8) {
        WSAAsyncSelect(Socket2, unknown_window_b263d8, 0, 0);
    }
}
