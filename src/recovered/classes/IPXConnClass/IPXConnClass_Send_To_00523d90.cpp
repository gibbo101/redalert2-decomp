// int IPXConnClass::Send_To(char *buf, int buflen, IPXAddressClass *address, unsigned char *immed, bool flagged, unsigned short id) (0x00523D90, slot 10)
// Sends a packet to an address (through a bridge network when given). A
// forwarded packet gets the connection's forwarding target (no target: not
// sent) and goes to the forwarding address, carrying the forwarding port
// unless that address is the first node's. In the game-mode 4 session the
// port comes from the session player of the connection.
#include "shared/ipx_manager.hpp"
#include "shared/owner_talk.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/session_state.hpp"
// @ref ??0IPXAddressClass@@QAE@XZ=00523410
// @ref ?Get_Address@IPXAddressClass@@QAEXQAE0@Z=00523500
// @ref ?Set_Address@IPXAddressClass@@QAEXQAE0G@Z=00523480
// @ref ??8IPXAddressClass@@QAE_NAAV0@@Z=005235d0
// @ref ?unknown_523690@IPXAddressClass@@QAE_NAAV1@@Z=00523690
// @ref ?unknown_flag_a3fba8@@3_NA=00a3fba8
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_OwnerTalkClass_00ab6d18@@3VOwnerTalkClass@@A=00ab6d18
// @ref ?Unknown_0063F4C0@OwnerTalkClass@@QAEEH@Z=0063f4c0
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_forward_address_a3fbac@@3VIPXAddressClass@@A=00a3fbac
// @ref ?unknown_forward_port_a3fbc4@@3HA=00a3fbc4
// @ref ?unknown_port_7f60dc@@3HA=007f60dc
// @ref ?unknown_forward_address_a3fbb8@@3VIPXAddressClass@@A=00a3fbb8
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50

int IPXConnClass::Send_To(char *buf, int buflen, IPXAddressClass *address, unsigned char *immed, bool flagged, unsigned short id)
{
    IPXAddressClass dest;
    dest = *address;
    if (immed) {
        NetNumType net;
        NetNodeType node;
        address->Get_Address(net, node);
        memcpy(net, immed, 4);
        dest.Set_Address(net, node, 0);
    }

    unsigned short port = 0;
    CommHeaderType *header = (CommHeaderType *)buf;
    if (!flagged && unknown_flag_a3fba8) {
        if (header->unknown_03 == 0) {
            unsigned char target = unknown_OwnerTalkClass_00ab6d18.Unknown_0063F4C0(ID);
            if (!target) {
                return 0;
            }
            header->unknown_03 = target;
        }
        dest = unknown_forward_address_a3fbac;
        port = unknown_port_7f60dc;
        if (unknown_forward_address_a3fbb8 == unknown_players_a3fa7c[0]->Address
            && dest.unknown_523690(unknown_players_a3fa7c[0]->Address)) {
            header->unknown_0c = 0;
            memset(&header->unknown_08, 0, sizeof(header->unknown_08));
        } else {
            port = unknown_forward_port_a3fbc4;
            header->unknown_0c = unknown_port_7f60dc;
            memset(&header->unknown_08, 0, sizeof(header->unknown_08));
        }
    } else {
        header->unknown_0c = 0;
        memset(&header->unknown_08, 0, sizeof(header->unknown_08));
    }

    if (unknown_game_mode_a3d298 == 4 && !unknown_flag_a3fba8) {
        int index = unknown_ipx_manager_a40978.unknown_slot19(this);
        switch (index) {
            case -4:
                if ((unsigned short)unknown_forward_port_a3fbc4) {
                    port = unknown_forward_port_a3fbc4;
                }
                break;
            case -3:
            case -2:
            case -1:
                break;
            default:
                if (index == 0 && unknown_flag_a3fba8) {
                    if ((unsigned short)unknown_forward_port_a3fbc4) {
                        port = unknown_forward_port_a3fbc4;
                    }
                } else if (index >= 0 && index < unknown_ipx_manager_a40978.Num_Connections()) {
                    port = unknown_session_a3d298.Unknown_00672F50(unknown_ipx_manager_a40978.Connection_ID(index));
                }
                break;
        }
    }

    if (PacketTransport) {
        PacketTransport->unknown_slot3(buf, buflen, &dest, sizeof(dest), flagged, 0, port);
    }
    return 1;
}
