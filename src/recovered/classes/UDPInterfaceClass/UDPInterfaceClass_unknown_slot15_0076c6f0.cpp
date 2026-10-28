// bool UDPInterfaceClass::unknown_slot15(int socket) (0x0076C6F0, slot 15)
// Starts Winsock if needed, opens the primary socket on the default port,
// records this host's addresses as the local addresses and opens the
// alternate socket on the alternate port.
#include "shared/udp_interface.hpp"
// @ref _closesocket@4=00781b96
// @ref _socket@12=00781ba2
// @ref _htons@4=00781b6c
// @ref _htonl@4=00781b66
// @ref _bind@12=00781b9c
// @ref _gethostname@8=00781bd2
// @ref _gethostbyname@4=00781b84
// @ref _WSAGetLastError@0=00781b7e
// @ref _setsockopt@20=00781ba8
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Set_Socket_Options@WinsockInterfaceClass@@UAE_NI@Z=0076b8f0
// @ref ?unknown_default_port_7f60d0@@3HA=007f60d0
// @ref ?unknown_alternate_port_7f60d8@@3HA=007f60d8
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BO@OJIG@About?5to?5query?5the?5host?5name?6?$AA@=008010d0
// @ref ??_C@_0BD@PBIF@Host?5name?5is?5?8?$CFs?8?6?$AA@=008010bc
// @ref ??_C@_0CC@GFGP@Found?5local?5address?3?5?$CFd?4?$CFd?4?$CFd?4?$CFd@=00801098
// @ref ??_C@_0CE@HMIH@About?5to?5open?5alternate?5UDP?5sock@=00801074
// @ref ??_C@_0BO@OJGD@About?5to?5bind?5the?5UDP?5socket?6?$AA@=00801054
// @ref ??_C@_0CE@LHNC@Alternate?5UDP?5Socket?5init?5comple@=00801030
// @ref ??_C@_0BN@JDKF@About?5to?5call?5gethostbyname?6?$AA@=007ff740
// @ref ??_C@_0CF@NPCK@gethostbyname?5failed?$CB?5Error?5code@=007e6554

bool UDPInterfaceClass::unknown_slot15(int)
{
    if (!WinsockInitialised && !unknown_slot25()) {
        return false;
    }
    Open_Socket(unknown_default_port_7f60d0);

    char name[128];
    Debug_Printf("About to query the host name\n");
    if (gethostname(name, sizeof(name))) {
        Debug_Printf("Host name is '%s'\n", name);
    }
    Debug_Printf("About to call gethostbyname\n");
    hostent *host = gethostbyname(name);
    if (!host) {
        Debug_Printf("gethostbyname failed! Error code %d\n", WSAGetLastError());
    }

    while (LocalAddresses.Count()) {
        delete LocalAddresses[0];
        LocalAddresses.Delete(0);
    }
    unsigned long **list = (unsigned long **)host->h_addr_list;
    while (*list) {
        unsigned long address = **list++;
        Debug_Printf("Found local address: %d.%d.%d.%d\n", address & 0xFF, (address >> 8) & 0xFF,
            (address >> 16) & 0xFF, address >> 24);
        unsigned char *local = new unsigned char[4];
        *(unsigned long *)local = address;
        LocalAddresses.Add(local);
    }

    Debug_Printf("About to open alternate UDP socket\n");
    Socket2 = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket2 == INVALID_SOCKET) {
        return false;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(unknown_alternate_port_7f60d8);
    addr.sin_addr = htonl(INADDR_ANY);
    Debug_Printf("About to bind the UDP socket\n");
    if (bind(Socket2, &addr, sizeof(addr)) == SOCKET_ERROR) {
        Close_Socket();
        return false;
    }

    linger nolinger;
    nolinger.l_onoff = 0;
    nolinger.l_linger = 0;
    setsockopt(Socket2, SOL_SOCKET, SO_LINGER, (char *)&nolinger, sizeof(nolinger));
    WinsockInterfaceClass::Set_Socket_Options(Socket2);
    Debug_Printf("Alternate UDP Socket init complete\n");
    return true;
}
