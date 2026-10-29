// void __fastcall Process_Timeouts_005bc500() (0x005BC500)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0BK@DJFE@Game?5?8?$CFls?8?5has?5timed?5out?6?$AA@=007e69dc
// @ref ?Refresh_Game_List_005bc790@@YAXXZ=005bc790
// @ref ?Unknown_005bbdd0@@YIX_N@Z=005bbdd0
// @ref ?Unknown_005c01d0@@YIXHHHH@Z=005c01d0
// @ref ?unknown_chat_a3fa4c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa4c
// @ref ?unknown_game_index_a71e90@@3HA=00a71e90
// @ref ?unknown_games_a3fa64@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa64
// @ref ?Refresh_Game_List_005bc790@@YIXXZ=005bc790
// @ref ?Delete@?$DynamicVectorClass@PAUNodeNameType@@@@QAE_NH@Z=005c2970

void __fastcall Process_Timeouts_005bc500()
{
    int i;

    for (i = 1; i < unknown_games_a3fa64.Count(); i++) {
        if (Compare_Wide_007837d3(unknown_games_a3fa64[i]->Name, unknown_host_name_a3f618) != 0) {
            if (TickCount.Time() - unknown_games_a3fa64[i]->Game.LastTime > 300) {
                Debug_Printf("Game '%ls' has timed out\n", unknown_games_a3fa64[i]->Name);
                delete unknown_games_a3fa64[i];
                unknown_games_a3fa64.Delete(unknown_games_a3fa64[i]);
                Refresh_Game_List_005bc790();
                if (i <= unknown_game_index_a71e90) {
                    Unknown_005bbdd0(false);
                    Unknown_005c01d0(0, 1, 0, 0);
                }
            }
        }
    }
    for (i = 1; i < unknown_chat_a3fa4c.Count(); i++) {
        if (unknown_chat_a3fa4c[i]->Chat.LastTime == 0) {
            unknown_chat_a3fa4c[i]->Chat.LastTime = TickCount.Time();
        }
        if (TickCount.Time() - unknown_chat_a3fa4c[i]->Chat.LastTime > 360) {
            delete unknown_chat_a3fa4c[i];
            unknown_chat_a3fa4c.Delete(unknown_chat_a3fa4c[i]);
            Unknown_005bbdd0(false);
        } else if (TickCount.Time() - unknown_chat_a3fa4c[i]->Chat.LastTime > 300 && unknown_chat_a3fa4c[i]->Chat.LastChance == 0) {
            UnknownGlobalPacket packet;
            memset(&packet, 0, sizeof(packet));
            strcpy(packet.Name, unknown_name_a3d3a0);
            packet.Command = 5;
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, &unknown_chat_a3fa4c[i]->Address, 0, 0);
            Service_Game_IO_00481fb0();
            unknown_chat_a3fa4c[i]->Chat.LastChance = 1;
        }
    }
}
