// bool IPXInterfaceClass::unknown_slot15(int socket_number) (0x0076A3A0, slot 15)
// Opens the IPX datagram socket on the socket number at the address of net
// card unknown_3f2f8 and sets its broadcast, packet type and filter options.
#include "shared/ipx_interface.hpp"
// @ref _socket@12=00781ba2
// @ref _bind@12=00781b9c
// @ref _closesocket@4=00781b96
// @ref _setsockopt@20=00781ba8
// @ref _htons@4=00781b6c
// @ref _WSAGetLastError@0=00781b7e
// @ref ?Init@WinsockInterfaceClass@@QAE_NXZ=0076b0a0
// @ref ?Set_Socket_Options@WinsockInterfaceClass@@UAE_NI@Z=0076b8f0
// @ref ?Get_Network_Card_Address@IPXInterfaceClass@@QAEHHPAUUnknownIPXSocketAddress@@@Z=0076a0b0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BL@NOPM@IPX?5Socket?5number?5is?5?$CF04x?6?$AA@=00800a74
// @ref ??_C@_0BP@MCGK@About?5to?5create?5an?5IPX?5socket?6?$AA@=00800a54
// @ref ??_C@_0CO@CAHB@Failed?5to?5create?5IPX?5socket?5?9?5er@=00800a24
// @ref ??_C@_0BH@JPCJ@IPX?5Socket?5created?5OK?6?$AA@=00800a0c
// @ref ??_C@_0DA@JCLO@IPX?5Error?5?9?5failed?5to?5get?5the?5ne@=008009dc
// @ref ??_C@_0EN@GFPN@IPX?5net?5card?5address?5is?5?$CF02x?5?$CF02@=0080098c
// @ref ??_C@_0BK@LBDI@About?5to?5bind?5IPX?5Socket?6?$AA@=00800970
// @ref ??_C@_0CM@NLLH@IPX?5socket?5bind?5failed?5with?5erro@=00800944
// @ref ??_C@_0BF@MGHL@IPX?5Socket?5bound?5OK?6?$AA@=0080092c
// @ref ??_C@_0CN@HLGH@About?5to?5set?5IPX?5socket?5option?5S@=008008fc
// @ref ??_C@_0DP@CFAP@Failed?5to?5set?5IPX?5socket?5option?5@=008008bc
// @ref ??_C@_0CH@GKND@IPX?5socket?5option?5SO_BROADCAST?5s@=00800894
// @ref ??_C@_0CK@ENFD@About?5to?5set?5IPX?5socket?5option?5I@=00800868
// @ref ??_C@_0DO@PCDK@Failed?5to?5set?5IPX?5protocol?5optio@=00800828
// @ref ??_C@_0CE@KDHJ@IPX?5socket?5option?5IPX_PTYPE?5set?5@=00800804
// @ref ??_C@_0CP@IIEI@About?5to?5set?5IPX?5socket?5option?5I@=008007d4
// @ref ??_C@_0ED@FGHK@Failed?5to?5set?5IPX?5protocol?5optio@=00800790
// @ref ??_C@_0CJ@BNMM@IPX?5socket?5option?5IPX_FILTERTYPE@=00800764
// @ref ??_C@_0BK@NJKP@IPX?5Socket?5init?5complete?6?$AA@=00800748

bool IPXInterfaceClass::unknown_slot15(int socket_number)
{
    if (!WinsockInitialised) {
        if (!Init()) {
            return false;
        }
    } else if (Socket != INVALID_SOCKET) {
        return false;
    }

    SocketNumber = socket_number;
    Debug_Printf("IPX Socket number is %04x\n", socket_number);
    UnknownIPXSocketAddress address;
    address.sa_family = 6;
    memset(address.sa_netnum, 0, sizeof(address.sa_netnum));
    memset(address.sa_nodenum, 0xFF, sizeof(address.sa_nodenum));
    address.sa_socket = htons(socket_number);

    Debug_Printf("About to create an IPX socket\n");
    Socket = socket(6, 2, 1000);
    if (Socket == INVALID_SOCKET) {
        Debug_Printf("Failed to create IPX socket - error code %d.\n", WSAGetLastError());
        closesocket(Socket);
        return false;
    }
    Debug_Printf("IPX Socket created OK\n");

    if (!Get_Network_Card_Address(unknown_3f2f8, &address)) {
        Debug_Printf("IPX Error - failed to get the net card address\n");
        closesocket(Socket);
        return false;
    }
    Debug_Printf("IPX net card address is %02x %02x %02x %02x : %02x %02x %02x %02x %02x %02x\n",
        address.sa_netnum[0], address.sa_netnum[1], address.sa_netnum[2], address.sa_netnum[3],
        address.sa_nodenum[0], address.sa_nodenum[1], address.sa_nodenum[2],
        address.sa_nodenum[3], address.sa_nodenum[4], address.sa_nodenum[5]);
    memcpy(unknown_3f306, address.sa_nodenum, sizeof(unknown_3f306));

    Debug_Printf("About to bind IPX Socket\n");
    if (bind(Socket, &address, 16) == SOCKET_ERROR) {
        Debug_Printf("IPX socket bind failed with error code %d.\n", WSAGetLastError());
        closesocket(Socket);
        return false;
    }
    Debug_Printf("IPX Socket bound OK\n");

    int broadcast = 1;
    int packet_type = 4;
    Debug_Printf("About to set IPX socket option SO_BROADCAST\n");
    if (setsockopt(Socket, 0xFFFF, 0x20, (char *)&broadcast, sizeof(broadcast)) == SOCKET_ERROR) {
        Debug_Printf("Failed to set IPX socket option SO_BROADCAST - error code %d.\n", WSAGetLastError());
    } else {
        Debug_Printf("IPX socket option SO_BROADCAST set OK\n");
    }
    Debug_Printf("About to set IPX socket option IPX_PTYPE\n");
    if (setsockopt(Socket, 1000, 0x4000, (char *)&packet_type, sizeof(packet_type)) == SOCKET_ERROR) {
        Debug_Printf("Failed to set IPX protocol option IPX_PTYPE - error code %d.\n", WSAGetLastError());
    } else {
        Debug_Printf("IPX socket option IPX_PTYPE set OK\n");
    }
    Debug_Printf("About to set IPX socket option IPX_FILTERTYPE\n");
    if (setsockopt(Socket, 1000, 0x4001, (char *)&packet_type, sizeof(packet_type)) == SOCKET_ERROR) {
        Debug_Printf("Failed to set IPX protocol option IPX_FILTERTYPE - error code %d.\n", WSAGetLastError());
    } else {
        Debug_Printf("IPX socket option IPX_FILTERTYPE set OK\n");
    }
    WinsockInterfaceClass::Set_Socket_Options(INVALID_SOCKET);
    Debug_Printf("IPX Socket init complete\n");
    return true;
}
