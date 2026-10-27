// bool WinsockInterfaceClass::Set_Socket_Options(SOCKET socket) (0x0076B8F0, slot 10)
// Sizes the receive and send buffers of a socket (the primary by default).
#include "shared/winsock_interface.hpp"
// @ref _setsockopt@20=00781ba8
// @ref _WSAGetLastError@0=00781b7e
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?SocketReceiveBuffer@WinsockInterfaceClass@@2HA=00800ac0
// @ref ?SocketSendBuffer@WinsockInterfaceClass@@2HA=00800abc
// @ref ??_C@_0CA@BIBE@Socket?5option?5SO_SNDBUF?5set?5OK?6?$AA@=00800d80
// @ref ??_C@_0DI@KKO@Failed?5to?5set?5socket?5option?5SO_S@=00800da0
// @ref ??_C@_0CA@CCIN@Socket?5option?5SO_RCVBUF?5set?5OK?6?$AA@=00800dd8
// @ref ??_C@_0DI@PGAN@Failed?5to?5set?5socket?5option?5SO_R@=00800df8

bool WinsockInterfaceClass::Set_Socket_Options(SOCKET socket)
{
    if (socket == INVALID_SOCKET) {
        socket = Socket;
    }
    if (setsockopt(socket, 0xFFFF, 0x1002, (char *)&SocketReceiveBuffer, 4) == SOCKET_ERROR) {
        Debug_Printf("Failed to set socket option SO_RCVBUF - error code %d.\n", WSAGetLastError());
    } else {
        Debug_Printf("Socket option SO_RCVBUF set OK\n");
    }
    if (setsockopt(socket, 0xFFFF, 0x1001, (char *)&SocketSendBuffer, 4) == SOCKET_ERROR) {
        Debug_Printf("Failed to set socket option SO_SNDBUF - error code %d.\n", WSAGetLastError());
    } else {
        Debug_Printf("Socket option SO_SNDBUF set OK\n");
    }
    return true;
}
