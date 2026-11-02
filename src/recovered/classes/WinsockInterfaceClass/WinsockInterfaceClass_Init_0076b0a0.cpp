// bool WinsockInterfaceClass::Init() (0x0076B0A0)
// Starts Winsock 1.1 (once), empties the buffers and takes the smallest
// usable maximum frame size of the UDP/IPX protocols as the packet size.
#include "shared/winsock_interface.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref __chkstk=00783850
// @ref _WSAStartup@8=00781bcc
// @ref _EnumProtocolsA@12=00781bc6
// @ref __imp__MessageBoxA@16=0079a47c
// @ref ?unknown_window_b263d8@@3PAXA=00b263d8
// @ref ?unknown_b2aea0@WinsockInterfaceClass@@2HA=00b2aea0
// @ref ?unknown_b2ae9c@WinsockInterfaceClass@@2_NA=00b2ae9c
// @ref ?Protocols@WinsockInterfaceClass@@2PAHA=00800ab0
// @ref ??_C@_0CC@JADJ@Winsock?5version?5is?5less?5than?51?41@=00800bfc
// @ref ??_C@_0CJ@HBNO@Found?5protocol?5?$CFs?0?5max?5frame?5siz@=00800c44
// @ref ??_C@_0CE@NLAI@Failed?5to?5get?5protocol?5enumerati@=00800c20
// @ref ??_C@_0BK@DKHE@Winsock?5version?5is?5?$CFd?4?$CFd?6?$AA@=00800c70
// @ref ??_C@_0BI@CLP@Winsock?5initialised?5OK?6?$AA@=00800c8c
// @ref ??_C@_0CP@NEHJ@Winsock?5failed?5to?5initialise?5?9?5e@=00800ca4
// @ref ??_C@_0BK@GKJF@About?5to?5call?5WSAStartup?6?$AA@=00800cd4
// @ref ??_C@_0CO@MEGD@Warning?5?9?5Packet?5Loss?5Simulation@=00800cf0
// @ref ??_C@_04PAEN@Note?$AA@=007d59f4
// @ref ??_C@_0CG@BCAM@WinsockInterface?5already?5initial@=00800d20
// @ref ??_C@_0BI@NICH@WinsockInterface?5init?4?6?$AA@=00800d48

bool WinsockInterfaceClass::Init()
{
    short version;
    int rc;

    Debug_Printf("WinsockInterface init.\n");
    if (WinsockInitialised) {
        Debug_Printf("WinsockInterface already initialised\n");
        return true;
    }
    if (unknown_b2aea0 > 0 && !unknown_b2ae9c) {
        unknown_b2ae9c = true;
        MessageBoxA(unknown_window_b263d8, "Warning - Packet Loss Simulation mode enabled", "Note", 0);
    }
    char *buffer = new char[sizeof(UnknownWinsockData)];
    UnknownWinsockData *winsock_info = (UnknownWinsockData *)(&buffer[0]);
    Socket = INVALID_SOCKET;
    Discard_In_Buffers();
    Discard_Out_Buffers();
    Debug_Printf("About to call WSAStartup\n");
    version = (1 << 8) | 1;
    rc = WSAStartup(version, winsock_info);
    if (rc) {
        Debug_Printf("Winsock failed to initialise - error code %d.\n", rc);
        delete [] buffer;
        return false;
    }
    Debug_Printf("Winsock initialised OK\n");
    if ((winsock_info->wVersion & 0x00ff) != (version & 0x00ff) ||
        (winsock_info->wVersion >> 8) != (version >> 8)) {
        Debug_Printf("Winsock version is less than 1.1\n");
        delete [] buffer;
        return false;
    }
    Debug_Printf("Winsock version is %d.%d\n", winsock_info->wVersion & 0x00ff, winsock_info->wVersion >> 8);

    unsigned long length;
    char protocol_buffer[4096];
    unknown_04 = 0x222;
    length = sizeof(protocol_buffer);
    int count = EnumProtocolsA(Protocols, protocol_buffer, &length);
    if (count != SOCKET_ERROR) {
        int max_frame = 0x7FFFFFFF;
        UnknownProtocolInfo *info = (UnknownProtocolInfo *)protocol_buffer;
        for (int i = 0; i < count; i++) {
            Debug_Printf("Found protocol %s, max frame size is %d\n", info[i].lpProtocol, info[i].dwMessageSize);
            int size = info[i].dwMessageSize;
            if (size != 0 && size != -1 && max_frame >= size) {
                max_frame = size;
            }
        }
        if (max_frame != 0x7FFFFFFF && max_frame > 400) {
            unknown_04 = max_frame;
        }
    } else {
        Debug_Printf("Failed to get protocol enumeration\n");
    }
    WinsockInitialised = true;
    delete [] buffer;
    return true;
}
