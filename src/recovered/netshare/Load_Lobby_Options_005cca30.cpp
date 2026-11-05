// void __fastcall Load_Lobby_Options_005cca30(HWND dialog, UnknownGameOptions *options) (0x005CCA30)
// Restores the lobby from a per-game-type settings block (the inverse of Save_Lobby_Options_005cc890):
// the game mode (the first registered mode when the saved one is unknown, or refuses a network session
// test through slot 1), the map (the mode's first playable map when it cannot play the saved one), each
// slot's entry kind (slots past the limit close; observers and computers fall back to open where they
// are not allowed), side and colour, then the session's game settings.
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/multi_mission.hpp"
#include "shared/multiplayer_game_mode.hpp"
// @ref ?Select_Scenario_005c7c30@@YI_NH@Z=005c7c30

void __fastcall Load_Lobby_Options_005cca30(HWND dialog, UnknownGameOptions *options)
{
    if (options->GameMode < 1 || options->GameMode > MultiplayerGameMode::unknown_mode_count_5b6f80()) {
        options->GameMode = MultiplayerGameMode::unknown_first_mode_5b6ec0()->Get_ID();
    }
    unknown_session_a3d298.GameModeIndex = options->GameMode;
    MultiplayerGameMode *mode = MultiplayerGameMode::unknown_find_mode_5b6fe0(unknown_session_a3d298.GameModeIndex);
    if (mode == 0) {
        mode = MultiplayerGameMode::unknown_first_mode_5b6ec0();
    }
    if ((unknown_73c370() || unknown_73c3a0()) && mode != 0 && mode->unknown_slot1()) {
        options->GameMode = MultiplayerGameMode::unknown_first_mode_5b6ec0()->Get_ID();
        unknown_session_a3d298.GameModeIndex = options->GameMode;
        MultiplayerGameMode *found = MultiplayerGameMode::unknown_find_mode_5b6fe0(unknown_session_a3d298.GameModeIndex);
        if (found == 0) {
            found = MultiplayerGameMode::unknown_first_mode_5b6ec0();
        }
        mode = found;
    }
    options->GameMode = mode->Get_ID();
    unknown_session_a3d298.GameModeIndex = mode->Get_ID();
    if (options->ScenIndex < 0 || options->ScenIndex >= unknown_session_a3d298.Scenarios.Count()) {
        options->ScenIndex = 0;
    }
    unknown_session_a3d298.ScenarioIndex = Select_Scenario_005c7c30(options->ScenIndex) ? options->ScenIndex : 0;
    MultiMission *scen = unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex];
    if (!mode->unknown_5b7470(scen)) {
        int index = mode->unknown_slot13();
        if (index == -1) {
            mode = MultiplayerGameMode::unknown_first_mode_5b6ec0();
            options->GameMode = mode->Get_ID();
            unknown_session_a3d298.GameModeIndex = mode->Get_ID();
            index = mode->unknown_slot13();
        }
        options->ScenIndex = index;
        unknown_session_a3d298.ScenarioIndex = index;
        Select_Scenario_005c7c30(index);
    }
    unknown_session_a3d298.Mode = mode;
    Select_Scenario_005c7c30(unknown_session_a3d298.ScenarioIndex);
    unknown_session_a3d298.Mode->unknown_slot8();
    unknown_session_a3d298.Mode->unknown_slot9();
    mode->unknown_slot6();
    mode->unknown_slot26();
    int limit = 8;
    if (unknown_game_mode_a3d298 == 4) {
        limit = (unknown_73c370() && !unknown_73c3a0()) ? 2 : 4;
    }
    if (unknown_lobby_flag_7e6d90 == 0 && limit < 8) {
        limit++;
    }
    for (int slot = 1; slot < 8; slot++) {
        int id = Slot_Control_Id_005c97a0(slot);
        int kind = options->Slots[slot][0];
        if (unknown_73c370() || unknown_lobby_flag_7e6d90 == 0 || unknown_a72c68 != 0) {
            if (kind == 4) {
                kind = 2;
            } else if (kind == 5) {
                kind = 2;
            } else if (kind == 6) {
                kind = 2;
            }
        }
        if (slot >= limit) {
            kind = 3;
        } else if (kind == 7) {
            kind = 2;
        }
        Select_Entry_Kind_005cc700(dialog, id, kind);
        int side_id = Player_Side_Combo_ID_4d1350(slot);
        int color_id = Player_Color_Combo_ID_4d1cb0(slot);
        if (kind != 2 && kind != 3) {
            if (kind == 7) {
                Select_Side_Combo_4d1a90(dialog, side_id, -3);
                Select_Color_Combo_4d2480(dialog, color_id, -2);
                HWND side = GetDlgItem(dialog, side_id);
                HWND colors = GetDlgItem(dialog, color_id);
                EnableWindow(side, FALSE);
                EnableWindow(colors, FALSE);
            } else {
                Select_Side_Combo_4d1a90(dialog, side_id, options->Slots[slot][1]);
                Set_Slot_Country_005c9a10(dialog, side_id);
                Select_Color_Combo_4d2480(dialog, color_id, options->Slots[slot][2]);
                Set_Slot_Color_005c9ab0(dialog, color_id);
            }
        } else {
            Select_Side_Combo_4d1a90(dialog, side_id, unknown_session_a3d298.Mode->unknown_slot10());
            Select_Color_Combo_4d2480(dialog, color_id, -2);
            HWND side = GetDlgItem(dialog, side_id);
            HWND colors = GetDlgItem(dialog, color_id);
            EnableWindow(side, FALSE);
            EnableWindow(colors, FALSE);
        }
    }
    unknown_session_a3d298.GameSpeed_30 = options->GameSpeed;
    unknown_session_a3d298.unknown_24 = options->Credits;
    unknown_session_a3d298.UnitCount = options->UnitCount;
    unknown_session_a3d298.unknown_2a = options->ShortGame;
    unknown_session_a3d298.unknown_2b = options->SuperWeaponsAllowed;
    unknown_session_a3d298.unknown_2c = options->BuildOffAlly;
    unknown_session_a3d298.unknown_a8 = options->MCVRepacks;
    unknown_session_a3d298.unknown_crates_29 = options->CratesAppear;
}
