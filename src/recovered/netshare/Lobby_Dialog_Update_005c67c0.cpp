// bool Lobby_Dialog_Update_005c67c0() (0x005C67C0)
// The lobby campaign dialog's update callback: a newly selected map row selects its map (a random
// map loads its preview), the selected row's text is kept, then the game mode's service runs.
#include "shared/lobby.hpp"
#include "shared/multi_mission.hpp"
#include "shared/map_preview.hpp"
#include "shared/ipx_conn.hpp"
// @ref ??_C@_0M@EOLM@RandMap?4img?$AA@=007e1540
// @ref ?Load_0061E170@UnknownPreview_0061D430@@QAEXPBD@Z=0061e170
// @ref ?unknown_lobby_dialog_a728e0@@3PAUHWND__@@A=00a728e0
// @ref ?unknown_lobby_map_a728d0@@3HA=00a728d0
// @ref ?unknown_lobby_map_a72c80@@3HA=00a72c80
// @ref ?unknown_lobby_map_name_a72a68@@3PAGA=00a72a68
// @ref ?Unknown_005bbd10@@YA_NXZ=005bbd10
// @ref ?Unknown_0073e100@@YA_NXZ=0073e100
// @ref ?Unknown_0059c880@@YA_NXZ=0059c880
// @ref ?Select_Scenario_005c7c30@@YI_NH@Z=005c7c30
// @ref ?Unknown_005c7570@@YIXPAUHWND__@@@Z=005c7570

bool Lobby_Dialog_Update_005c67c0()
{
    int row = Selected_Campaign_005c67a0();
    if (row != -1) {
        MultiMission *mission = (MultiMission *)SendDlgItemMessageA(unknown_lobby_dialog_a728e0, 0x553, 0x199, row, 0);
        int found = -1;
        for (int i = 0; i < unknown_multi_missions_a3d8d8.Count(); i++) {
            if (mission == unknown_multi_missions_a3d8d8[i]) {
                found = i;
                break;
            }
        }
        if (found != -1 && found != unknown_lobby_map_a728d0) {
            Select_Scenario_005c7c30(found);
            if (unknown_multi_missions_a3d8d8[found]->Unknown_006720C0()) {
                delete unknown_dialog_preview_a72ce8;
                unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
                unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
                if (unknown_dialog_preview_a72ce8->unknown_00 == 0) {
                    Unknown_005c7570(unknown_lobby_dialog_a728e0);
                }
                InvalidateRect(unknown_lobby_dialog_a728e0, 0, 0);
            } else {
                Unknown_005c7570(unknown_lobby_dialog_a728e0);
            }
            unknown_lobby_map_a728d0 = found;
            unknown_session_a3d2b4 = unknown_lobby_map_a72c80;
            Select_Scenario_005c7c30(unknown_session_a3d2b4);
        }
    }
    HWND dialog = unknown_lobby_dialog_a728e0;
    row = Selected_Campaign_005c67a0();
    wchar_t const *name;
    if (row != -1 && (name = (wchar_t const *)SendDlgItemMessageA(dialog, 0x553, 0x199, row, 0)) != 0) {
        wcscpy(unknown_lobby_map_name_a72a68, name);
    } else {
        unknown_lobby_map_name_a72a68[0] = 0;
    }
    if (unknown_game_mode_a3d298 == 3) {
        return Unknown_005bbd10();
    }
    if (unknown_game_mode_a3d298 == 4) {
        return Unknown_0073e100();
    }
    if (unknown_game_mode_a3d298 == 1 || unknown_game_mode_a3d298 == 2) {
        return Unknown_0059c880();
    }
    Service_Game_IO_00481fb0();
    return false;
}
