// bool WinsockInterfaceClass::Start_Listening() (0x0076AE80, slot 7)
// Asks for read and write notifications on both sockets.
#include "shared/winsock_interface.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref _WSAAsyncSelect@16=00781bc0
// @ref _WSAGetLastError@0=00781b7e
// @ref ?unknown_window_b263d8@@3PAXA=00b263d8
// @ref ??_C@_0DK@HMNL@Async?5select?5failed?5on?5alternate@=00800b88
// @ref ??_C@_0DI@PEAJ@Async?5select?5failed?5on?5primary?5s@=00800bc4

bool WinsockInterfaceClass::Start_Listening()
{
    if (WSAAsyncSelect(Socket, unknown_window_b263d8, unknown_slot14(-1), 3) == SOCKET_ERROR) {
        Debug_Printf("Async select failed on primary socket - error code %d.\n", WSAGetLastError());
        return false;
    }
    if (Socket2 != INVALID_SOCKET) {
        if (WSAAsyncSelect(Socket2, unknown_window_b263d8, unknown_slot14(Socket2), 3) == SOCKET_ERROR) {
            Debug_Printf("Async select failed on alternate socket - error code %d.\n", WSAGetLastError());
            return false;
        }
    }
    return true;
}
