// int IPXGlobalConnClass::Send_To(char *buf, int buflen, IPXAddressClass *address, unsigned char *immed, bool flagged, unsigned short id) (0x00524B50, slot 10)
// Sends a packet to an address (through a bridge network when given). In the
// forwarding session (game mode 4) an untargeted header gets the target of the
// node whose address matches (1 when none), and the packet goes to the
// forwarding address; the header carries the forwarding port unless that
// address is the first node's.
#include "shared/ipx_global_conn.hpp"
#include "shared/owner_talk.hpp"
#include "shared/unknown_player_entry.hpp"
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

int IPXGlobalConnClass::Send_To(char *buf, int buflen, IPXAddressClass *address, unsigned char *immed, bool flagged, unsigned short id)
{
    IPXAddressClass dest;
    NetNumType net;
    NetNodeType node;
    dest = *address;
    if (immed) {
        address->Get_Address(net, node);
        memcpy(net, immed, 4);
        dest.Set_Address(net, node, 0);
    }

    unsigned short port;
    CommHeaderType *header = (CommHeaderType *)buf;
    if (unknown_game_mode_a3d298 == 4 && !flagged && unknown_flag_a3fba8 && unknown_c8) {
        if (header->unknown_03 == 0) {
            IPXAddressClass sender = dest;
            sender.Get_Address(net, node);
            sender.Set_Address(net, node, id);
            int target_id = -1;
            for (int i = 0; i < unknown_players_a3fa7c.Count(); i++) {
                if (unknown_players_a3fa7c[i]->Address == sender) {
                    target_id = unknown_players_a3fa7c[i]->ID;
                    break;
                }
            }
            unsigned char target = unknown_OwnerTalkClass_00ab6d18.Unknown_0063F4C0(target_id);
            if (!target) {
                target = 1;
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
        port = id;
    }

    if (PacketTransport) {
        PacketTransport->unknown_slot3(buf, buflen, &dest, sizeof(dest), flagged, !unknown_c8, port);
    }
    return 1;
}
