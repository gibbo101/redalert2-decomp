// bool UDPInterfaceClass::Open_Spare_Socket(unsigned short port) (0x0076C480, slot 26)
// Opens another datagram socket bound to the port, unless the port is 0 or
// already has one.
#include "shared/udp_interface.hpp"
// @ref _closesocket@4=00781b96
// @ref _socket@12=00781ba2
// @ref _htons@4=00781b6c
// @ref _htonl@4=00781b66
// @ref _bind@12=00781b9c
// @ref ?Set_Socket_Options@WinsockInterfaceClass@@UAE_NI@Z=0076b8f0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0CJ@GDHB@About?5to?5bind?5the?5UDP?5socket?5to?5@=00800f44
// @ref ??_C@_0CA@NPOB@About?5to?5open?5spare?5UDP?5socket?6?$AA@=00800ff4
// @ref ??_C@_0BF@OELP@Got?5spare?5socket?5?$CFd?6?$AA@=00800fdc
// @ref ??_C@_0CI@IGHL@Failed?5to?5bind?5spare?5socket?5to?5p@=00800fb4
// @ref ??_C@_0CA@NDJO@Spare?5UDP?5Socket?5init?5complete?6?$AA@=00800f94

bool UDPInterfaceClass::Open_Spare_Socket(unsigned short port)
{
    if (!port) {
        return false;
    }
    for (int i = 0; i < NumSockets; i++) {
        if (SocketPorts[i] == port) {
            return false;
        }
    }

    Debug_Printf("About to open spare UDP socket\n");
    SOCKET spare = socket(AF_INET, SOCK_DGRAM, 0);
    if (spare == INVALID_SOCKET) {
        return false;
    }
    Debug_Printf("Got spare socket %d\n", spare);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = htonl(INADDR_ANY);
    Debug_Printf("About to bind the UDP socket to port %d\n", port);
    if (bind(spare, &addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(spare);
        Debug_Printf("Failed to bind spare socket to port %d\n", port);
        return false;
    }

    SocketPorts[NumSockets] = port;
    Sockets[NumSockets] = spare;
    NumSockets++;
    WinsockInterfaceClass::Set_Socket_Options(spare);
    Debug_Printf("Spare UDP Socket init complete\n");
    return true;
}
