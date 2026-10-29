// void Send_Slot_Names_005bbd20() (0x005BBD20)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"

void Send_Slot_Names_005bbd20()
{
    UnknownGlobalPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x16;
    strcpy(packet.Name, unknown_name_a3d3a0);
    Unknown_Slot_Names_005c8cf0(packet.Slots.Names);
    int count = unknown_players_a3fa7c.Count();
    for (int i = 1; i < count; i++) {
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
        Service_Game_IO_00481fb0();
    }
}
