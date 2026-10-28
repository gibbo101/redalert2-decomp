// char *IPXAddressClass::As_String_00523840(IPXAddressClass const *address) (0x00523840)
// The address (this one when null) as text in a static buffer: the network
// and node bytes in hex (IPX), or the IP and the port (UDP; the port is
// always this object's).
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"
// @ref ?IPXProtocol@@3HA=007ddc70
// @ref _sprintf=007820f4
// @ref ?unknown_address_text_a522e4@@3PADA=00a522e4
// @ref ??_C@_0BB@IJI@?$CFd?4?$CFd?4?$CFd?4?$CFd?5?$DL?5?$CFd?$AA@=007ddc74
// @ref ??_C@_0DE@BPMD@?$CF02X?5?$CF02X?5?$CF02X?5?$CF02X?5?3?5?$CF02X?5?$CF02X?5@=007ddc88

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
// The text buffer of As_String (0x00A522E4).
extern char unknown_address_text_a522e4[];

char *IPXAddressClass::As_String_00523840(IPXAddressClass const *address)
{
    if (!address) {
        address = this;
    }
    NetNodeType node;
    memcpy(node, address->NodeAddress, sizeof(node));
    if (IPXProtocol == 1) {
        NetNumType net;
        memcpy(net, address->NetworkNumber, sizeof(net));
        sprintf(unknown_address_text_a522e4, "%02X %02X %02X %02X : %02X %02X %02X %02X %02X %02X", net[0], net[1], net[2], net[3],
            node[0], node[1], node[2], node[3], node[4], node[5]);
    } else {
        sprintf(unknown_address_text_a522e4, "%d.%d.%d.%d ; %d", node[0], node[1], node[2], node[3], *(unsigned short *)NetworkNumber);
    }
    return unknown_address_text_a522e4;
}
