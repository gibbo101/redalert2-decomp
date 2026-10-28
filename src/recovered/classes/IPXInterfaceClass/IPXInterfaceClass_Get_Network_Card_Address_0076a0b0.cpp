// int IPXInterfaceClass::Get_Network_Card_Address(int card_number, UnknownIPXSocketAddress *address) (0x0076A0B0)
// The network and node of an adapter, read through a temporary bound IPX
// socket; the network is also kept in Network. 0 on failure.
#include "shared/ipx_interface.hpp"
// @ref _socket@12=00781ba2
// @ref _bind@12=00781b9c
// @ref _closesocket@4=00781b96
// @ref _getsockopt@20=00781b90
// @ref _WSAGetLastError@0=00781b7e
// @ref ?unknown_flag_839c4c@@3_NA=00839c4c
// @ref ?unknown_839bc0@@3HA=00839bc0
// @ref ?unknown_839bc4@@3HA=00839bc4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0DP@NINP@getsockopt?5with?5IPX_MAX_ADAPTER_@=008006a8
// @ref ??_C@_0DH@ILJM@Failed?5to?5get?5address?5of?5net?5car@=00800638
// @ref ??_C@_0DH@OHHB@Skipping?5IPX_MAX_ADAPTER_NUM?5cal@=00800670

int IPXInterfaceClass::Get_Network_Card_Address(int card_number, UnknownIPXSocketAddress *address)
{
    SOCKET s = socket(6, 2, 1000);
    if (s == INVALID_SOCKET) {
        return 0;
    }

    UnknownIPXSocketAddress ipx;
    memset(&ipx, 0, sizeof(ipx));
    ipx.sa_family = 6;
    if (bind(s, &ipx, sizeof(ipx)) == SOCKET_ERROR) {
        closesocket(s);
        return 0;
    }

    int adapters = 1;
    int length = sizeof(adapters);
    bool win95 = unknown_flag_839c4c && unknown_839bc0 == 4 && unknown_839bc4 == 0;
    if (!win95) {
        if (getsockopt(s, 1000, 0x400D, (char *)&adapters, &length) == 0) {
            if (card_number >= adapters) {
                return 0;
            }
        } else {
            Debug_Printf("getsockopt with IPX_MAX_ADAPTER_NUM failed with error code %d\n", WSAGetLastError());
        }
    } else {
        Debug_Printf("Skipping IPX_MAX_ADAPTER_NUM call due to bug in Win95\n");
    }

    UnknownIPXAddressData data;
    memset(&data, 0, sizeof(data));
    data.adapternum = card_number;
    int data_length = sizeof(data);
    if (getsockopt(s, 1000, 0x4007, (char *)&data, &data_length) == SOCKET_ERROR) {
        Debug_Printf("Failed to get address of net card %d - error code %d.\n", card_number, WSAGetLastError());
        closesocket(s);
        return 0;
    }
    memcpy(address->sa_netnum, data.netnum, 4);
    memcpy(Network, data.netnum, 4);
    memcpy(address->sa_nodenum, data.nodenum, 6);
    closesocket(s);
    return 1;
}
