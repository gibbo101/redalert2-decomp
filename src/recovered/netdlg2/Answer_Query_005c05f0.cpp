// bool __fastcall Answer_Query_005c05f0(UnknownGlobalPacket *packet, IPXAddressClass *address) (0x005C05F0)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/taunt_packet.hpp"
#include "shared/session_state.hpp"
// @ref ?Value_011c_00672a10@UnknownSessionState@@QAEHXZ=00672a10
// @ref ?Value_0124_006729f0@UnknownSessionState@@QAEHXZ=006729f0
// @ref ?unknown_a71bc4@@3PADA=00a71bc4
// @ref ?unknown_join_state_a71e94@@3HA=00a71e94
// @ref ?unknown_session_a3f614@@3_NA=00a3f614
// @ref ?unknown_session_a3f616@@3_NA=00a3f616
// @ref ?unknown_session_a40d04@@3_NA=00a40d04

bool __fastcall Answer_Query_005c05f0(UnknownGlobalPacket *packet, IPXAddressClass *address)
{
    if (packet->Command == 0 && !unknown_session_a3f614) {
        if (wcslen(unknown_host_name_a3f618) > 0) {
            if (!unknown_session_a3f616 || Compare_Narrow_00781f20(unknown_name_a3d3a0, Unknown_006FA120(unknown_host_name_a3f618)) == 0) {
                if (Compare_Narrow_00781f20(unknown_name_a3d3a0, Unknown_006FA120(unknown_host_name_a3f618)) != 0 && !unknown_session_a40d04) {
                    return true;
                }
                UnknownGlobalPacket answer;
                memset(&answer, 0, sizeof(answer));
                answer.Command = 1;
                strcpy(answer.Name, Unknown_006FA120(unknown_host_name_a3f618));
                answer.GameInfo.IsOpen = unknown_session_a3f616;
                unknown_ipx_manager_a40978.Send_Global_Message(&answer, sizeof(answer), 1, address, 0, 0);
            }
        }
        return true;
    }
    if (packet->Command == 2) {
        if (Compare_Narrow_00781f20(packet->Name, Unknown_006FA120(unknown_host_name_a3f618)) == 0
            && wcslen(unknown_host_name_a3f618) > 0 && !unknown_session_a3f614 && unknown_join_state_a71e94 >= 2) {
            UnknownGlobalPacket answer;
            memset(&answer, 0, sizeof(answer));
            answer.Command = 3;
            strcpy(answer.Name, unknown_name_a3d3a0);
            strcpy(answer.unknown_18, unknown_a71bc4);
            answer.PlayerInfo.unknown_2f = unknown_session_a3d298.Value_0124_006729f0();
            answer.PlayerInfo.unknown_33 = unknown_session_a3d298.Value_011c_00672a10();
            answer.PlayerInfo.unknown_37 = Unknown_005bba50(unknown_host_name_a3f618);
            answer.PlayerInfo.Slot = unknown_lobby_a3fa94;
            answer.PlayerInfo.Observer = unknown_lobby_a3fa94 == unknown_lobby_flag_7e6d90;
            if (unknown_players_a3fa7c.Count() == 0) {
                return true;
            }
            if (unknown_players_a3fa7c[0]->Team != -1) {
                answer.PlayerInfo.Observer = 0;
            }
            unknown_ipx_manager_a40978.Send_Global_Message(&answer, sizeof(answer), 1, address, 0, 0);
            if (Compare_Narrow_00781f20(packet->Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name)) == 0) {
                Unknown_005c3810(true, true);
                if (unknown_session_a3d29c) {
                    unknown_session_a3d29c->unknown_slot20();
                }
            }
            return true;
        }
    }
    return false;
}
