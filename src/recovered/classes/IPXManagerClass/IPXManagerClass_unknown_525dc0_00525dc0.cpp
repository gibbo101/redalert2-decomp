// bool IPXManagerClass::unknown_525dc0(CommHeaderType *header, char *buf, int buflen, IPXAddressClass *address, unsigned short port) (0x00525DC0)
// In the forwarding session with a router process: a packet that carries the
// forwarder port goes to the local router with the sender's node and port in
// its header; a packet with a forwarding target that is not this node goes on
// to that target. Returns whether the packet was forwarded.
#include "shared/ipx_manager.hpp"
#include "shared/owner_talk.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_flag_a3fba8@@3_NA=00a3fba8
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_OwnerTalkClass_00ab6d18@@3VOwnerTalkClass@@A=00ab6d18
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_port_7f60dc@@3HA=007f60dc
// @ref ?unknown_node_ids_a402ba@@3PAGA=00a402ba
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50
// @ref ??_C@_0CN@EOBI@Forwarding?5packet?5from?5?$CFs?5?$DL?5?$CFd?5t@=007de030
// @ref ??_C@_0EI@ODOI@Packet?5is?5supposed?5to?5be?5forward@=007ddfe8
// @ref ??_C@_0CF@DLAK@Forwarding?5packet?5from?5router?5to@=007ddfc0
// @ref _?$S56@?1??unknown_525dc0@IPXManagerClass@@QAE_NPAUCommHeaderType@@PADHPAVIPXAddressClass@@G@Z@4EA=00a524cc
// @ref _?loopback@?1??unknown_525dc0@IPXManagerClass@@QAE_NPAUCommHeaderType@@PADHPAVIPXAddressClass@@G@Z@4UUnknownLoopbackAddress@@A=00a524fc

// The local router's address (the network number, then the IP 127.0.0.1;
// passed as a 12-byte address).
struct UnknownLoopbackAddress {
    NetNumType NetworkNumber;
    unsigned long NodeAddress;
};

bool IPXManagerClass::unknown_525dc0(CommHeaderType *header, char *buf, int buflen, IPXAddressClass *address, unsigned short port)
{
    static UnknownLoopbackAddress loopback = { {0}, htonl(0x7F000001) };

    if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8 && unknown_OwnerTalkClass_00ab6d18.RouterProcess) {
        if (header->unknown_0c == unknown_port_7f60dc) {
            header->unknown_0c = port;
            memcpy(&header->unknown_08, address->NodeAddress, 4);
            Debug_Printf("Forwarding packet from %s ; %d to forwarder\n", address->As_String_00523840(), port);
            PacketTransport->unknown_slot3(buf, buflen, &loopback, sizeof(IPXAddressClass), false, 1, unknown_port_7f60dc);
            return true;
        }
        if (header->unknown_0c != 0) {
            NetNodeType node;
            unknown_players_a3fa7c[0]->Address.Get_Node(node);
            if (memcmp(node, &header->unknown_08, 4) == 0 && unknown_node_ids_a402ba[0] == header->unknown_0c) {
                Debug_Printf("Packet is supposed to be forwarded to us - just adding it to our queue\n");
            } else if (header->unknown_08 != 0) {
                unsigned short target_port = header->unknown_0c;
                IPXAddressClass target;
                NetNodeType ip;
                memcpy(ip, &header->unknown_08, 4);
                target.Set_Node(ip);
                target.unknown_523960(target_port);
                header->unknown_0c = 0;
                memset(&header->unknown_08, 0, sizeof(header->unknown_08));
                Debug_Printf("Forwarding packet from router to %s\n", target.As_String_00523840());
                PacketTransport->unknown_slot3(buf, buflen, &target, sizeof(target), false, 1, target_port);
                return true;
            }
        }
    }
    return false;
}
