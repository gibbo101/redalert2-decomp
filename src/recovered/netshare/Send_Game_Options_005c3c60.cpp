// void __fastcall Send_Game_Options_005c3c60(char const *text) (0x005C3C60)
// Under World Online the text goes to the chat server as the public game options; otherwise a global
// packet 0x17 with the local nick name, the text, the colour and the host name's CRC goes to every other
// player, serving the game I/O after each send.
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/game_options_packet.hpp"
#include "shared/debug_printf.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/wol_chat.hpp"
// @ref ??_C@_0CD@PNIB@Sending?5public?5game?5options?5to?5?$CF@=007e6e5c

void __fastcall Send_Game_Options_005c3c60(char const *text)
{
    if (unknown_chat_a72cfc != 0) {
        char buffer[1024];
        strncpy(buffer, text, sizeof(buffer) - 1);
        unknown_chat_a72cfc->unknown_slot15(buffer);
        return;
    }
    UnknownOptionsPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x17;
    strcpy(packet.Name, unknown_name_a3d3a0);
    strcpy(packet.Text, text);
    packet.Color = unknown_a3d3b4;
    packet.NameCRC = Unknown_005bba50(unknown_host_name_a3f618);
    for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
        NodeNameType *player = unknown_players_a3fa7c[i];
        Debug_Printf("Sending public game options to %s\n", Unknown_006FA120(player->Name));
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &player->Address, 0, 0);
        Service_Game_IO_00481fb0();
    }
}
