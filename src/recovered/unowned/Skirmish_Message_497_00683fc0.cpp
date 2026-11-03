// Populates the skirmish dialog from the saved settings and selected map.
#include "shared/skirmish.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/multi_mission.hpp"
#include "shared/map_preview.hpp"
#include "shared/rules.hpp"
#include "shared/string_table.hpp"
int __fastcall Skirmish_Message_497(HWND dialog, WPARAM wparam, LPARAM lparam)
{
    unknown_lobby_state_a3d2b0.Unknown_00672810();
    HWND item = GetDlgItem(dialog, 0x6A0);
    if (item) {
        SendMessageA(item, 0xC5, 19, 0);
        SendMessageA(item, 0x4B2, 0, (LPARAM)Unknown_006FA180(unknown_name_a3d3a0));
        SendMessageA(item, 0x4D1, 1, 0);
    }
    for (int i = 0; i < 7; ++i) {
        item = GetDlgItem(dialog, Skirmish_Player_Combo_ID(i));
        SendMessageA(item, 0x14B, 0, 0);
        int index = SendMessageA(item, 0x4C2, 0, (LPARAM)StringTable::Load_String("GUI:None", 0, "D:\\Ra2\\Skirmish.cpp", 0x9C));
        SendMessageA(item, 0x151, index, -1);
        index = SendMessageA(item, 0x4C2, 0, (LPARAM)StringTable::Load_String("GUI:AIEasy", 0, "D:\\Ra2\\Skirmish.cpp", 0x9F));
        SendMessageA(item, 0x151, index, 2);
        index = SendMessageA(item, 0x4C2, 0, (LPARAM)StringTable::Load_String("GUI:AINormal", 0, "D:\\Ra2\\Skirmish.cpp", 0xA2));
        SendMessageA(item, 0x151, index, 1);
        index = SendMessageA(item, 0x4C2, 0, (LPARAM)StringTable::Load_String("GUI:AIHard", 0, "D:\\Ra2\\Skirmish.cpp", 0xA5));
        SendMessageA(item, 0x151, index, 0);
        SendMessageA(item, 0x14E, 0, 0);
    }
    Fill_Side_Combos_4d16d0(dialog);
    Init_Color_Entries_4d1ea0();
    Fill_Color_Combos_4d2300(dialog);
    Select_Player_Side_4d1820(dialog, 0);
    Select_Player_Color_4d23c0(dialog, 0);
    for (int player = 1; player < 8; ++player) {
        int combo = Skirmish_Player_Combo_ID(player - 1);
        int type = unknown_session_a3d298.SkirmishOptions.Slots[player][0];
        int selected;
        if (type == 1) selected = -1;
        else if (type == 4) selected = 0;
        else if (type == 5) selected = 1;
        else if (type == 6) selected = 2;
        else selected = -1;
        int count = SendDlgItemMessageA(dialog, combo, 0x146, 0, 0);
        for (int row = 0; row < count; ++row) {
            if (SendDlgItemMessageA(dialog, combo, 0x150, row, 0) == selected) {
                SendDlgItemMessageA(dialog, combo, 0x14E, row, 0);
                break;
            }
        }
        int side = Player_Side_Combo_ID_4d1350(player);
        int color = Player_Color_Combo_ID_4d1cb0(player);
        if (selected == -1) {
            Select_Side_Combo_4d1a90(dialog, side, -2);
            Select_Color_Combo_4d2480(dialog, color, -2);
            HWND side_window = GetDlgItem(dialog, side);
            HWND color_window = GetDlgItem(dialog, color);
            EnableWindow(side_window, false);
            EnableWindow(color_window, false);
        } else {
            Select_Side_Combo_4d1a90(dialog, side, unknown_session_a3d298.SkirmishOptions.Slots[player][1]);
            Select_Color_Combo_4d2480(dialog, color, unknown_session_a3d298.SkirmishOptions.Slots[player][2]);
        }
    }
    if (unknown_session_a3d298.SkirmishOptions.GameMode < 0 || unknown_session_a3d298.SkirmishOptions.GameMode >= MultiplayerGameMode::unknown_mode_count_5b6f80()) {
        unknown_session_a3d298.SkirmishOptions.GameMode = MultiplayerGameMode::unknown_first_mode_5b6ec0()->unknown_28;
    }
    unknown_session_a3d298.GameModeIndex = unknown_session_a3d298.SkirmishOptions.GameMode;
    MultiplayerGameMode *mode = Current_Game_Mode_005c34d0();
    unknown_session_a3d298.SkirmishOptions.GameMode = mode->unknown_28;
    unknown_session_a3d298.GameModeIndex = mode->unknown_28;
    if (unknown_session_a3d298.SkirmishOptions.ScenIndex < 0 || unknown_session_a3d298.SkirmishOptions.ScenIndex >= unknown_multi_missions_a3d8d8.Count()) unknown_session_a3d298.SkirmishOptions.ScenIndex = 0;
    unknown_session_a3d298.ScenarioIndex = Select_Scenario_005c7c30(unknown_session_a3d298.SkirmishOptions.ScenIndex) ? unknown_session_a3d298.SkirmishOptions.ScenIndex : 0;
    MultiMission *map = unknown_multi_missions_a3d8d8[unknown_session_a3d298.ScenarioIndex];
    if (!mode->unknown_5b7470(map)) {
        int selection = mode->unknown_slot13();
        if (selection == -1) {
            mode = MultiplayerGameMode::unknown_first_mode_5b6ec0();
            unknown_session_a3d298.SkirmishOptions.GameMode = mode->unknown_28;
            unknown_session_a3d298.GameModeIndex = mode->unknown_28;
            selection = mode->unknown_slot13();
        }
        map = unknown_multi_missions_a3d8d8[selection];
        unknown_session_a3d298.SkirmishOptions.ScenIndex = selection;
        unknown_session_a3d298.ScenarioIndex = selection;
    }
    int scenario = unknown_session_a3d298.ScenarioIndex;
    int players = Unknown_005c6600(scenario);
    if (scenario == -1) {
        Skirmish_Hide_Players(dialog, 1);
        Skirmish_Show_Players(dialog, 1, players - 1);
    }
    int extra = players - 8;
    if (extra > 0) Skirmish_Show_Players(dialog, 8, extra);
    else if (extra < 0) Skirmish_Hide_Players(dialog, players);
    unknown_session_a3d298.Mode = mode;
    mode->unknown_slot8();
    Unknown_005c3450(dialog, mode);
    Unknown_005c34b0(dialog);
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
    unknown_session_a3d298.GameSpeed_30 = unknown_session_a3d298.SkirmishOptions.GameSpeed;
    unknown_session_a3d298.unknown_24 = unknown_session_a3d298.SkirmishOptions.Credits;
    unknown_session_a3d298.UnitCount = unknown_session_a3d298.SkirmishOptions.UnitCount;
    item = GetDlgItem(dialog, 0x529);
    if (item) {
        int speed = 6 - unknown_session_a3d298.GameSpeed_30;
        SendMessageA(item, 0x406, 1, 0x60000);
        SendMessageA(item, 0x405, 1, speed);
    }
    item = GetDlgItem(dialog, 0x511);
    if (item) {
        SendMessageA(item, 0x406, 1, ((unsigned int)(unsigned short)Rules->MaxMoney << 16) | (unsigned short)Rules->MinMoney);
        SendMessageA(item, 0x405, 1, unknown_session_a3d298.unknown_24);
        SendMessageA(item, 0x4AB, 0, Rules->MoneyIncrement);
    }
    item = GetDlgItem(dialog, 0x50C);
    if (item) {
        SendMessageA(item, 0x406, 1, ((unsigned int)(unsigned short)Rules->MaxUnitCount << 16) | (unsigned short)Rules->MinUnitCount);
        SendMessageA(item, 0x405, 1, unknown_session_a3d298.UnitCount);
    }
    unknown_session_a3d298.unknown_2a = unknown_session_a3d298.SkirmishOptions.ShortGame;
    unknown_session_a3d298.unknown_2b = unknown_session_a3d298.SkirmishOptions.SuperWeaponsAllowed;
    unknown_session_a3d298.unknown_2c = unknown_session_a3d298.SkirmishOptions.BuildOffAlly;
    unknown_session_a3d298.unknown_a8 = unknown_session_a3d298.SkirmishOptions.MCVRepacks;
    unknown_session_a3d298.unknown_crates_29 = unknown_session_a3d298.SkirmishOptions.CratesAppear;
    item = GetDlgItem(dialog, 0x54E);
    if (item) SendMessageA(item, 0xF1, unknown_session_a3d298.unknown_2a != false, 0);
    item = GetDlgItem(dialog, 0x69A);
    if (item) SendMessageA(item, 0xF1, unknown_session_a3d298.unknown_2b != false, 0);
    item = GetDlgItem(dialog, 0x69D);
    if (item) SendMessageA(item, 0xF1, unknown_session_a3d298.unknown_2c != false, 0);
    item = GetDlgItem(dialog, 0x693);
    if (item) SendMessageA(item, 0xF1, unknown_session_a3d298.unknown_a8 != false, 0);
    item = GetDlgItem(dialog, 0x696);
    if (item) SendMessageA(item, 0xF1, unknown_session_a3d298.unknown_crates_29 != false, 0);
    if (map->Unknown_006720C0()) {
        if (unknown_dialog_preview_a72ce8) delete unknown_dialog_preview_a72ce8;
        unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
        unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
        if (!unknown_dialog_preview_a72ce8->unknown_00) Unknown_005c7570(dialog);
    } else Unknown_005c7570(dialog);
    return 0;
}

// @ref ??_C@_08DOEP@GUI?3None?$AA@=007f4008
// @ref ??_C@_0M@EOLM@RandMap?4img?$AA@=007e1540
// @ref ??_C@_0L@OJFC@GUI?3AIHard?$AA@=007e72b8
// @ref ??_C@_0N@GOPO@GUI?3AINormal?$AA@=007e72c4
// @ref ??_C@_0L@JIHB@GUI?3AIEasy?$AA@=007e72d4
// @ref ??_C@_0BE@OMOF@D?3?2Ra2?2Skirmish?4cpp?$AA@=007f3fd4
