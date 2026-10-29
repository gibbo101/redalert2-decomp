// void __fastcall Unjoin_Game_005c00b0(int game) (0x005C00B0)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
// @ref ?unknown_games_a3fa64@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa64
// @ref ?unknown_join_state_a71e94@@3HA=00a71e94

void __fastcall Unjoin_Game_005c00b0(int game)
{
    UnknownGlobalPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 10;
    strcpy(packet.Name, unknown_name_a3d3a0);
    for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
        Service_Game_IO_00481fb0();
    }
    if (unknown_join_state_a71e94 == 1 || unknown_join_state_a71e94 == 2) {
        if (!unknown_games_a3fa64[game]->Address.Is_Broadcast()) {
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_games_a3fa64[game]->Address, 0, 0);
        }
    }
    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, 0, 0, 0);
    Clear_Slot_Lists_005c8a70();
    Fill_Slots_005c8a10();
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
    unknown_host_name_a3f618[0] = 0;
}
