// void __fastcall Unknown_005c3d90(char const *name, char const *text) (0x005C3D90)
// Sends game options text privately to the player called name: under World Online as a chat page to that
// user; otherwise as a global packet 0x18 (local nick name and the text) to each other player whose narrowed
// name matches, serving the game I/O after each send. The colour and host CRC go into the session's own
// packet (unknown_gpacket_a3f640), not the sent copy.
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/game_options_packet.hpp"
#include "shared/debug_printf.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/wol_chat.hpp"
#include "shared/session_state.hpp"
// @ref ??_C@_0CF@ELF@Sending?5private?5game?5options?5to?5@=007e6e80

void __fastcall Unknown_005c3d90(char const *name, char const *text)
{
    WOL::IChat *chat = unknown_chat_a72cfc;
    if (chat != 0) {
        WOL::User user;
        memset(&user, 0, sizeof(user));
        strcpy(user.name, name);
        chat->unknown_slot14(&user, text);
        return;
    }
    UnknownOptionsPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x18;
    strcpy(packet.Name, unknown_name_a3d3a0);
    strcpy(packet.Text, text);
    ((UnknownOptionsPacket &)unknown_gpacket_a3f640).Color = unknown_session_a3d298.Value_011c_00672a10();
    ((UnknownOptionsPacket &)unknown_gpacket_a3f640).NameCRC = Unknown_005bba50(unknown_host_name_a3f618);
    for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
        if (_stricmp(Unknown_006FA120(unknown_players_a3fa7c[i]->Name), name) == 0) {
            Debug_Printf("Sending private game options to %ls\n", unknown_players_a3fa7c[i]->Name);
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
            Service_Game_IO_00481fb0();
        }
    }
}
