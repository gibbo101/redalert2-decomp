// void __fastcall Destroy_Connection_005bb5d0(int id, int error) (0x005BB5D0)
// TibSun/Red Alert netdlg.cpp Destroy_Connection: a network player has gone.
// Shows "connection lost" (error 1) or "left the game" (error 0), deletes the
// IPX connection, sends REMOVEPLAYER (or, before the first frame, hands the
// house to the computer) or, for a player who left, tells the packet router;
// when this player is the game master behind the packet router, hands the
// router to the next host; then removes the player from the session list.
#include "shared/queue.hpp"
#include "shared/event.hpp"
#include "shared/netdlg.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/gadget.hpp"
#include "shared/vector_class.hpp"
#include "shared/session_state.hpp"
#include "shared/owner_talk.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_conn.hpp"
#include "shared/connection.hpp"
#include "shared/debug_printf.hpp"

extern bool unknown_flag_a40d1c;    // 0x00A40D1C (session +0x3A84: trace the connections)
extern bool unknown_a402d8;
// @ref ?unknown_flag_a40d1c@@3_NA=00a40d1c
// @ref ?unknown_a402d8@@3_NA=00a402d8
// @ref ?Unknown_00672F20@UnknownSessionState@@QAEXH@Z=00672f20
// @ref ?Unknown_0063F130@OwnerTalkClass@@QAE_NXZ=0063f130
// @ref ?Unknown_0063FBA0@OwnerTalkClass@@QAEHXZ=0063fba0
// @ref ?Unknown_0063FE20@OwnerTalkClass@@QAEXH@Z=0063fe20
// @ref ?Am_I_Master@UnknownSessionState@@QAE_NPAVHouseClass@@@Z=0066f150
// @ref ??_C@_0BG@PAMP@New?5game?5host?5is?5?$CFls?6?$AA@=007d6934
// @ref ??_C@_0BP@KEPE@Session?4PacketRouterPort?5?$DN?5?$CFd?6?$AA@=007d694c
// @ref ??_C@_0CC@HDKL@Session?4PacketRouterAddress?5?$DN?5?$CFs@=007d696c
// @ref ??_C@_0BE@DDAG@TXT_CONNECTION_LOST?$AA@=007e6954
// @ref ??_C@_0O@JGPN@TXT_LEFT_GAME?$AA@=007e6930
// @ref ??_C@_0BC@LAEF@D?3?2Ra2?2NetDlg?4CPP?$AA@=007e6940
// @ref ??_C@_0CK@MIFM@Destroying?5connection?5for?5house?5@=007e6968
// @ref ?Add_Message@MessageListClass@@QAEPAVUnknownMessageNode@@PBGH0HIH_N@Z=005b4da0
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref ??3@YAXPAX@Z=00781d3b
// @ref __ftol=0077f110
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __real@8@4008e100000000000000=0079b608

void __fastcall Destroy_Connection_005bb5d0(int id, int error)
{
    int i;
    HouseClass *housep;
    wchar_t txt[80];

    housep = Houses[id];

    if (unknown_flag_a40d1c) {
        Debug_Printf("Destroying connection for house %d (%ls)\n", id, housep->UIName);
    }

    if (!housep || !housep->unknown_134) {
        return;
    }

    txt[0] = 0;
    if (error == 1) {
        swprintf(txt, StringTable::Load_String("TXT_CONNECTION_LOST", 0, "D:\\Ra2\\NetDlg.CPP", 0x1CF), housep->UIName);
    } else if (error == 0) {
        swprintf(txt, StringTable::Load_String("TXT_LEFT_GAME", 0, "D:\\Ra2\\NetDlg.CPP", 0x1D1), housep->UIName);
    }

    if (wcslen(txt)) {
        unknown_session_a3d298.Messages.Add_Message(0, 0, txt, housep->Type->Color, 0x4046, Rules->MessageDelay * 900, false);
        Map.Flag_To_Redraw(false);
    }

    unknown_ipx_manager_a40978.Delete_Connection(id);

    if (error) {
        if (Frame == 0) {
            housep->unknown_func_4e7e80();
        } else {
            OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x23, id));
        }
    } else {
        if (unknown_game_mode_a3d298 == 4 && unknown_b2a7ec) {
            housep->unknown_func_4e7e80();
        }
        if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8) {
            unknown_OwnerTalkClass_00ab6d18.Unknown_0063FE20(id);
        }
    }

    if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8 && unknown_session_a3d298.Am_I_Master(housep)) {
        unknown_a402d8 = true;
        int host = unknown_OwnerTalkClass_00ab6d18.Unknown_0063FBA0();
        if (host != -1) {
            HouseClass *hostp = Houses[host];
            if (hostp) {
                if (unknown_session_a3d298.Players.Count() > 2) {
                    IPXAddressClass *address = 0;
                    for (i = 0; i < unknown_session_a3d298.Players.Count(); i++) {
                        if (unknown_session_a3d298.Players[i]->ID == host) {
                            address = &unknown_session_a3d298.Players[i]->Address;
                            unknown_session_a3d298.unknown_292c = unknown_node_ids_a402ba[i];
                            break;
                        }
                    }
                    unsigned char network[4];
                    unsigned char node[6];
                    address->Get_Address(network, node);
                    unknown_forward_address_a3fbac.Set_Address(network, node, 0);
                    Debug_Printf("Session.PacketRouterAddress = %s\n", unknown_forward_address_a3fbac.As_String_00523840(0));
                    Debug_Printf("Session.PacketRouterPort = %d\n", unknown_session_a3d298.unknown_292c);
                    unknown_ipx_manager_a40978.unknown_5277c0(&unknown_forward_address_a3fbac);
                }
                wcscpy(unknown_session_a3d298.MasterPlayerName, hostp->UIName);
                Debug_Printf("New game host is %ls\n", unknown_session_a3d298.MasterPlayerName);
                unknown_session_a3d298.MasterPlayerID = host;
                if (unknown_session_a3d298.Am_I_Master(0)) {
                    unknown_OwnerTalkClass_00ab6d18.Unknown_0063F130();
                }
            }
        }
    }

    for (i = 0; i < unknown_session_a3d298.Players.Count(); i++) {
        if (unknown_session_a3d298.Players[i]->ID == id) {
            delete unknown_session_a3d298.Players[i];
            unknown_session_a3d298.Players.Delete(unknown_session_a3d298.Players[i]);
            unknown_session_a3d298.Unknown_00672F20(i);
            if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8) {
                unknown_OwnerTalkClass_00ab6d18.Unknown_0063FE20(id);
            }
            break;
        }
    }

    unknown_session_a3d55c--;
}
