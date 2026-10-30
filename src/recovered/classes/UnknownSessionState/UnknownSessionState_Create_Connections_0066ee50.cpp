#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/session_state.hpp"
#include "shared/vector_class.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/ipx_address.hpp"
#include "shared/ipx_conn.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/owner_talk.hpp"
#include "shared/house.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/debug_printf.hpp"
int UnknownSessionState::Create_Connections()
{
    NetNumType net;
    NetNodeType node;

    Debug_Printf("Entering Create_Connections\n");
    if (unknown_game_mode_a3d298 != 3 && unknown_game_mode_a3d298 != 4) {
        return 0;
    }

    for (int i = 0; i < Players.Count(); i++) {
        Debug_Printf("Player %d, Name: %s, ID %d\n", i, Players[i]->Name, Players[i]->ID);
        if (_wcsicmp(Players[i]->Name, Houses[Players[i]->ID]->UIName) != 0) {
            return 0;
        }
        if (_wcsicmp(Players[i]->Name, MasterPlayerName) == 0) {
            MasterPlayerID = Players[i]->ID;
            unknown_players_a3fa7c[i]->Address.Get_Address(net, node);
            unknown_forward_address_a3fbac.Set_Address(net, node, 0);
            unknown_ipx_manager_a40978.unknown_5277c0(&unknown_forward_address_a3fbac);
        }
        Houses[Players[i]->ID]->unknown_14c = Players[i]->unknown_6b;
        unknown_players_a3fa7c[i]->Address.Get_Address(net, node);
        unsigned long ip = 0;
        for (int j = 0; j < 4; j++) {
            ip = (ip << 8) | node[j];
        }
        Debug_Printf("House[%d] IP = %X  Clan=%d\n", Players[i]->ID, ip, Players[i]->unknown_6b);
        Houses[Players[i]->ID]->unknown_148 = ip;
        Houses[Players[i]->ID]->unknown_150 = false;
        if (i > 0) {
            unknown_ipx_manager_a40978.Create_Connection(Players[i]->ID, Players[i]->Name, &Players[i]->Address);
            Players[i]->unknown_63 = -1;
        }
    }

    for (int k = 0; k < 8; k++) {
        unknown_session_a3d298.unknown_2ff4[k] = TickCount.Time();
    }

    if (Type == 4 && unknown_3038) {
        NetNumType net2;
        NetNodeType node2;
        net2[0] = 0;
        net2[1] = 0;
        net2[2] = 0;
        net2[3] = 0;
        node2[0] = 0;
        node2[1] = 0;
        node2[2] = 0;
        node2[3] = 0;
        node2[4] = 0;
        node2[5] = 0;
        unknown_forward_address_a3fbb8.Set_Address(net2, node2, 0);
        ViaPacketRouter = true;
        unknown_3034 = 0;
        unknown_3044 = 20;
        unknown_303c = -1;
        unknown_ipx_manager_a40978.unknown_5255b0();
        unknown_OwnerTalkClass_00ab6d18.Unknown_0063F2A0();
        if (unknown_session_a3d298.Am_I_Master(0)) {
            bool connected = unknown_OwnerTalkClass_00ab6d18.Unknown_0063F510(0);
            if (connected) {
                connected = unknown_OwnerTalkClass_00ab6d18.Unknown_0063F130();
            }
            if (!connected) {
                unknown_flag_a3fba8 = false;
            }
        }
    } else {
        unknown_flag_a3fba8 = false;
    }
    Debug_Printf("Session.ViaPacketRouter = %s\n", unknown_flag_a3fba8 ? "true" : "false");
    Debug_Printf("Leaving Create_Connections\n");
    return 1;
}
// @ref ??_C@_0BM@LIPL@Leaving?5Create_Connections?6?$AA@=007f3410
// @ref ??_C@_0BO@BENC@Session?4ViaPacketRouter?5?$DN?5?$CFs?6?$AA@=007f342c
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_0BM@GOIL@House?$FL?$CFd?$FN?5IP?5?$DN?5?$CFX?5?5Clan?$DN?$CFd?6?$AA@=007f344c
// @ref ??_C@_0BM@NICG@Player?5?$CFd?0?5Name?3?5?$CFs?0?5ID?5?$CFd?6?$AA@=007f3468
// @ref ??_C@_0BN@JHPO@Entering?5Create_Connections?6?$AA@=007f3484
// @ref ?Unknown_0063F130@OwnerTalkClass@@QAE_NXZ=0063f130
// @ref ?Unknown_0063F2A0@OwnerTalkClass@@QAEXXZ=0063f2a0
// @ref ?Unknown_0063F510@OwnerTalkClass@@QAE_NH@Z=0063f510
