// void __fastcall Unknown_005c01d0(int gamenow, int playernow, int chatnow, int init) (0x005C01D0)
// Red Alert's Send_Join_Queries: the game query every 120 ticks, the player query of the selected game every 35
// and the chat announcement every 83 (function-local timers; their atexit destructors are 0x5C05E0, 0x5C05D0
// and 0x5C05C0; the $E/$S numbers are this unit's). Session.Handle and Session.Games are read
// through the session object (Games is NodeList_27cc): the alias forms swap the Games[CurGame] load order.
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref _atexit=0078298a
// @ref ?Current_Dialog_Id_00735b20@@YAHXZ=00735b20
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref ?Send_Global_Message@IPXManagerClass@@QAEHPAXHHPAVIPXAddressClass@@GK@Z=00525830
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref ?unknown_dest_net_set_a3f604@@3HA=00a3f604
// @ref ?unknown_dest_net_a3f608@@3VIPXAddressClass@@A=00a3f608
// @ref ?unknown_game_index_a71e90@@3HA=00a71e90
// @ref ?unknown_join_state_a71e94@@3HA=00a71e94
// @ref ?unknown_games_a3fa64@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa64
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_session_a3d298@@3VUnknownSessionState@@A=00a3d298
// @ref _?$S28@?1??Unknown_005c01d0@@YIXHHHH@Z@4EA=00a71e74
// @ref _?game_timer@?1??Unknown_005c01d0@@YIXHHHH@Z@4V?$CDTimerClass@VSystemTimerClass@@@@A=00a71e68
// @ref _?player_timer@?1??Unknown_005c01d0@@YIXHHHH@Z@4V?$CDTimerClass@VSystemTimerClass@@@@A=00a71e48
// @ref _?chat_timer@?1??Unknown_005c01d0@@YIXHHHH@Z@4V?$CDTimerClass@VSystemTimerClass@@@@A=00a71bb8

void __fastcall Unknown_005c01d0(int gamenow, int playernow, int chatnow, int init)
{
    static CDTimerClass<SystemTimerClass> game_timer;
    static CDTimerClass<SystemTimerClass> player_timer;
    static CDTimerClass<SystemTimerClass> chat_timer;
    UnknownGlobalPacket packet;

    if (init) {
        game_timer = 120;
        player_timer = 35;
        chat_timer = 83;
    }

    if (!game_timer || gamenow) {
        game_timer = 120;
        if (Current_Dialog_Id_00735b20() != 0xBC || gamenow) {
            memset(&packet, 0, sizeof(packet));
            packet.Command = 0;
            strcpy(packet.Name, unknown_session_a3d298.Handle);
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, 0, 0, 0);
            if (unknown_dest_net_set_a3f604) {
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, &unknown_dest_net_a3f608, 0, 0);
            }
        }
    }

    if ((unknown_game_index_a71e90 > 0 && unknown_game_index_a71e90 < unknown_games_a3fa64.Count() && !player_timer) || playernow) {
        player_timer = 35;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 2;
        strcpy(packet.Name, Unknown_006FA120(unknown_session_a3d298.NodeList_27cc[unknown_game_index_a71e90]->Name));
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, 0, 0, 0);
        if (unknown_dest_net_set_a3f604) {
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, &unknown_dest_net_a3f608, 0, 0);
        }
    }

    if ((!chat_timer && unknown_join_state_a71e94 < 2) || chatnow) {
        chat_timer = 83;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 4;
        strcpy(packet.Name, unknown_session_a3d298.Handle);
        packet.Chat.ID = unknown_session_a3d298.UniqueID;
        packet.Chat.Color = unknown_a3d3b4;
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, 0, 0, 0);
        if (unknown_dest_net_set_a3f604) {
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, &unknown_dest_net_a3f608, 0, 0);
        }
    }
}
