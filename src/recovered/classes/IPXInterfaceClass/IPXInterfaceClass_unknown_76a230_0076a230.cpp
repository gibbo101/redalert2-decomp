// int IPXInterfaceClass::unknown_76a230(int card_number, char *buffer, int length) (0x0076A230)
// A network card's address as text ("net : node" in hex).
#include "shared/ipx_interface.hpp"
// @ref _sprintf=007820f4
// @ref ?Get_Network_Card_Address@IPXInterfaceClass@@QAEHHPAUUnknownIPXSocketAddress@@@Z=0076a0b0
// @ref ??_C@_0DE@KIIG@?$CF02x?5?$CF02x?5?$CF02x?5?$CF02x?5?3?5?$CF02x?5?$CF02x?5@=008006e8
// @ref ??_C@_0CM@FMKG@?$DP?$DP?5?$DP?$DP?5?$DP?$DP?5?$DP?$DP?5?3?5?$CF02x?5?$CF02x?5?$CF02x?5?$CF02@=0080071c

int IPXInterfaceClass::unknown_76a230(int card_number, char *buffer, int length)
{
    if (!WinsockInitialised) {
        return 0;
    }
    UnknownIPXSocketAddress address;
    char text[256];
    int result = Get_Network_Card_Address(card_number, &address);
    if (result) {
        if (result == 2) {
            sprintf(text, "?? ?? ?? ?? : %02x %02x %02x %02x %02x %02x",
                address.sa_nodenum[0], address.sa_nodenum[1], address.sa_nodenum[2],
                address.sa_nodenum[3], address.sa_nodenum[4], address.sa_nodenum[5]);
        } else {
            sprintf(text, "%02x %02x %02x %02x : %02x %02x %02x %02x %02x %02x",
                address.sa_netnum[0], address.sa_netnum[1], address.sa_netnum[2], address.sa_netnum[3],
                address.sa_nodenum[0], address.sa_nodenum[1], address.sa_nodenum[2],
                address.sa_nodenum[3], address.sa_nodenum[4], address.sa_nodenum[5]);
        }
        if ((int)strlen(text) >= length) {
            return 0;
        }
        strcpy(buffer, text);
    }
    return result;
}
