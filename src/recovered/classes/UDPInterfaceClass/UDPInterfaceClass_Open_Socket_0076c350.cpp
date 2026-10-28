// bool UDPInterfaceClass::Open_Socket(unsigned short port) (0x0076C350, slot 23)
// (Re)opens the primary datagram socket and binds it to the port (the
// default game port when 0), with lingering off.
#include "shared/udp_interface.hpp"
// @ref _closesocket@4=00781b96
// @ref _socket@12=00781ba2
// @ref _htons@4=00781b6c
// @ref _htonl@4=00781b66
// @ref _bind@12=00781b9c
// @ref _WSAGetLastError@0=00781b7e
// @ref _setsockopt@20=00781ba8
// @ref ?Set_Socket_Options@WinsockInterfaceClass@@UAE_NI@Z=0076b8f0
// @ref ?unknown_default_port_7f60d0@@3HA=007f60d0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0CC@FMML@About?5to?5open?5primary?5UDP?5socket@=00800f70
// @ref ??_C@_0CJ@GDHB@About?5to?5bind?5the?5UDP?5socket?5to?5@=00800f44
// @ref ??_C@_0CA@IAOD@Bind?5failed?5with?5error?5code?5?$CFd?6?$AA@=00800f24
// @ref ??_C@_0CC@PEFM@Primary?5UDP?5Socket?5init?5complete@=00800f00

bool UDPInterfaceClass::Open_Socket(unsigned short port)
{
    if (Socket != INVALID_SOCKET) {
        closesocket(Socket);
        Socket = INVALID_SOCKET;
    }
    Debug_Printf("About to open primary UDP socket\n");
    Socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket == INVALID_SOCKET) {
        return false;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    if (port) {
        unknown_3f2fc = port;
        addr.sin_port = htons(port);
    } else {
        unknown_3f2fc = 0;
        addr.sin_port = htons(unknown_default_port_7f60d0);
    }
    addr.sin_addr = htonl(INADDR_ANY);
    Debug_Printf("About to bind the UDP socket to port %d\n", port);
    if (bind(Socket, &addr, sizeof(addr)) == SOCKET_ERROR) {
        Debug_Printf("Bind failed with error code %d\n", WSAGetLastError());
        Close_Socket();
        return false;
    }

    linger nolinger;
    nolinger.l_onoff = 0;
    nolinger.l_linger = 0;
    setsockopt(Socket, SOL_SOCKET, SO_LINGER, (char *)&nolinger, sizeof(nolinger));
    WinsockInterfaceClass::Set_Socket_Options(INVALID_SOCKET);
    Debug_Printf("Primary UDP Socket init complete\n");
    return true;
}
