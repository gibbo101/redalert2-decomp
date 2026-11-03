// void __fastcall Skirmish_Command(HWND dialog, int id, HWND control, int code) (0x006829F0)
// WM_COMMAND of the skirmish dialog: a player-type change enables that row's side and
// colour boxes, the side and colour boxes update their row, 0x5AA picks another map
// in the lobby dialog, and 0x5C0/0x617 check the players and store the settings in
// the session (0x617 starts the game: the id goes to the dialog's DWL_USER result).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/skirmish.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/multi_mission.hpp"
#include "shared/map_preview.hpp"
#include "shared/string_table.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/modem_guest.hpp"
// @ref ?Unknown_005e5fc0@@YIXPAUHWND__@@@Z=005e5fc0
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BO@JKCN@TXT_NEED_AT_LEAST_TWO_PLAYERS?$AA@=007f3fe8
// @ref ??_C@_0BH@KOPH@TXT_SCENARIO_TOO_SMALL?$AA@=007e24cc
// @ref ??_C@_0BE@OMOF@D?3?2Ra2?2Skirmish?4cpp?$AA@=007f3fd4
// @ref ??_C@_0M@EOLM@RandMap?4img?$AA@=007e1540
// @ref ??_EWstring@@QAEPAXI@Z=0040af40
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c

// (0x005E5FC0; before the lobby dialog opens over the skirmish dialog; not recovered.)
void __fastcall Unknown_005e5fc0(HWND dialog);

// A code-free GetDlgItem wrapper (hypothesis, see VC6_MATCHING_NOTES "Import-call wrappers"); its sites, with
// the row helper below, leave the original's /Ob2 allowance at the row helper, which then calls
// Skirmish_Is_Computer 0x006836B0 where the player loops expand it.
static inline HWND Get_Item(HWND window, int id)
{
    return GetDlgItem(window, id);
}

// A player-type combo changed: a human row gets the random side and colour and only a computer row may
// pick them (expanded into Skirmish_Command).
static void Skirmish_Player_Type_Changed(HWND dialog, int id)
{
    int player = Skirmish_Player_Index(id) + 1;
    int color_id = Player_Color_Combo_ID_4d1cb0(player);
    int side_id = Player_Side_Combo_ID_4d1350(player);
    unsigned char computer = Skirmish_Is_Computer(dialog, id);
    if (!computer) {
        Select_Color_Combo_4d2480(dialog, color_id, -2);
        Select_Side_Combo_4d1a90(dialog, side_id, -2);
    }
    HWND color_box = Get_Item(dialog, color_id);
    HWND side_box = Get_Item(dialog, side_id);
    EnableWindow(color_box, computer);
    EnableWindow(side_box, computer);
}

void __fastcall Skirmish_Command(HWND dialog, int id, HWND control, int code)
{
    int *result = (int *)GetWindowLongA(dialog, DWL_USER);
    switch (id) {
    case 0x50B:
    case 0x50E:
    case 0x516:
    case 0x51A:
    case 0x51B:
    case 0x51C:
    case 0x51D:
        Skirmish_Player_Type_Changed(dialog, id);
        return;
    case 0x5AA: {
        int old_mode = unknown_session_a3d298.GameModeIndex;
        int old_scenario = unknown_session_a3d298.ScenarioIndex;
        char old_file[0x200];
        strcpy(old_file, unknown_session_a3d298.ScenarioFileName_658);
        wchar_t old_name[0x100];
        wcscpy(old_name, unknown_map_name_a3d342);
        Unknown_005e5fc0(dialog);
        ShowWindow(dialog, SW_HIDE);
        if (Open_Lobby_Dialog_005c6960((HWND)unknown_b263d8) == 2) {
            unknown_session_a3d298.GameModeIndex = old_mode;
            unknown_session_a3d298.ScenarioIndex = old_scenario;
            Select_Scenario_005c7c30(old_scenario);
            Unknown_005c7570(dialog);
            ShowWindow(dialog, SW_SHOW);
            if (unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->Unknown_006720C0()) {
                if (unknown_dialog_preview_a72ce8) {
                    delete unknown_dialog_preview_a72ce8;
                }
                unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
                unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
                if (!unknown_dialog_preview_a72ce8->Is_Present()) {
                    Unknown_005c7570(dialog);
                }
                InvalidateRect(dialog, 0, 0);
            } else {
                Unknown_005c7570(dialog);
            }
            InvalidateRect(dialog, 0, 0);
            return;
        }
        int scenario = unknown_session_a3d298.ScenarioIndex;
        int old_players;
        if (old_scenario == -1) {
            old_players = 8;
        } else {
            old_players = Unknown_005c6600(old_scenario);
        }
        int players = Unknown_005c6600(scenario);
        int extra = players - old_players;
        if (old_scenario == scenario) {
            Skirmish_Hide_Players(dialog, 1);
            Skirmish_Show_Players(dialog, 1, players - 1);
        }
        if (extra > 0) {
            Skirmish_Show_Players(dialog, old_players, extra);
        } else if (extra < 0) {
            Skirmish_Hide_Players(dialog, players);
        }
        ShowWindow(dialog, SW_SHOW);
        if (Select_Scenario_005c7c30(unknown_session_a3d298.ScenarioIndex)) {
            Unknown_005c3450(dialog, MultiplayerGameMode::unknown_find_mode_5b6fe0(unknown_session_a3d298.GameModeIndex));
            Unknown_005c34b0(dialog);
            if (unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->Unknown_006720C0()) {
                if (unknown_dialog_preview_a72ce8) {
                    delete unknown_dialog_preview_a72ce8;
                    unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
                    unknown_dialog_preview_a72ce8->Load_0061E170("RandMap.img");
                }
                if (!unknown_dialog_preview_a72ce8->Is_Present()) {
                    Unknown_005c7570(dialog);
                }
                InvalidateRect(dialog, 0, 0);
            } else {
                Unknown_005c7570(dialog);
            }
        } else {
            unknown_session_a3d298.ScenarioIndex = old_scenario;
            unknown_session_a3d298.GameModeIndex = old_mode;
        }
        return;
    }
    case 0x5C0:
    case 0x617: {
        if (code != 0) {
            break;
        }
        if (id == 0x617) {
            EnableWindow(Get_Item(dialog, 0x617), 0);
        }
        int players = Unknown_005c6600(unknown_session_a3d298.ScenarioIndex);
        int computers = 0;
        int index;
        for (index = 0; index < 7; index++) {
            if (Skirmish_Is_Computer(dialog, Skirmish_Player_Combo_ID(index))) {
                computers++;
            }
        }
        int total = computers + 1;
        unknown_session_a3d298.AICount = computers;
        if (id == 0x617) {
            wchar_t text[0x100];
            if (players < total) {
                swprintf(text, StringTable::Load_String("TXT_SCENARIO_TOO_SMALL", 0, "D:\\Ra2\\Skirmish.cpp", 0x334), players);
                WWMessageBox(L" ").Process(text, StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\Skirmish.cpp", 0x335), 0, 0, false);
                EnableWindow(Get_Item(dialog, 0x617), 1);
                return;
            }
            if (total <= 1) {
                swprintf(text, StringTable::Load_String("TXT_NEED_AT_LEAST_TWO_PLAYERS", 0, "D:\\Ra2\\Skirmish.cpp", 0x33C), players);
                WWMessageBox(L" ").Process(text, StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\Skirmish.cpp", 0x33D), 0, 0, false);
                EnableWindow(Get_Item(dialog, 0x617), 1);
                return;
            }
        }
        MultiplayerGameMode *mode = unknown_session_a3d298.Mode;
        WideString message;
        if (!mode->unknown_slot5(&message)) {
            if (id == 0x617) {
                WWMessageBox(L" ").Process(message.Get(), StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\Skirmish.cpp", 0x34B), 0, 0, false);
                EnableWindow(Get_Item(dialog, 0x617), 1);
                return;
            }
            MultiplayerGameMode::unknown_first_mode_5b6ec0();
        }
        unknown_session_a3d298.SkirmishOptions.GameMode = unknown_session_a3d298.GameModeIndex;
        unknown_session_a3d298.SkirmishOptions.ScenIndex = unknown_session_a3d298.ScenarioIndex;
        if (unknown_session_a3d298.ScenarioIndex >= unknown_session_a3d298.Scenarios.Count()) {
            unknown_session_a3d298.SkirmishOptions.ScenIndex = 0;
        }
        wchar_t name[20];
        HWND edit = Get_Item(dialog, 0x6A0);
        SendMessageA(edit, 0x4B3, 20, (LPARAM)name);
        Unknown_006FA0F0(unknown_session_a3d298.Handle, name, -1);
        int local_side = Side_Combo_Data_4d1c70(dialog, 0x6A1, -1);
        unknown_session_a3d298.Set_Value_00672a30(local_side, true);
        for (index = 0; index < 7; index++) {
            int player = index + 1;
            int combo = Skirmish_Player_Combo_ID(index);
            int side_id = Player_Side_Combo_ID_4d1350(player);
            int color_id = Player_Color_Combo_ID_4d1cb0(player);
            if (Skirmish_Is_Computer(dialog, combo)) {
                int difficulty = SendDlgItemMessageA(dialog, combo, CB_GETCURSEL, 0, 0);
                unknown_session_a3d298.AIDifficulty[player] = SendDlgItemMessageA(dialog, combo, CB_GETITEMDATA, difficulty, 0);
                unknown_session_a3d298.AICountry[player] = Side_Combo_Data_4d1c70(dialog, side_id, -1);
                unknown_session_a3d298.AIColor[player] = Color_Combo_Data_4d2900(dialog, color_id, -1);
            }
        }
        for (int player = 1; player < 8; player++) {
            int combo = Skirmish_Player_Combo_ID(player - 1);
            int side_id = Player_Side_Combo_ID_4d1350(player);
            int color_id = Player_Color_Combo_ID_4d1cb0(player);
            int selected = SendDlgItemMessageA(dialog, combo, CB_GETCURSEL, 0, 0);
            int type = SendDlgItemMessageA(dialog, combo, CB_GETITEMDATA, selected, 0);
            int side = Side_Combo_Data_4d1c70(dialog, side_id, -1);
            int color = Color_Combo_Data_4d2900(dialog, color_id, -1);
            int value;
            if (type == -1) {
                value = 1;
            } else if (type == 0) {
                value = 4;
            } else if (type == 1) {
                value = 5;
            } else {
                value = type == 2 ? 6 : 0;
            }
            unknown_session_a3d298.SkirmishOptions.Slots[player][0] = value;
            unknown_session_a3d298.SkirmishOptions.Slots[player][1] = side;
            unknown_session_a3d298.SkirmishOptions.Slots[player][2] = color;
        }
        int local_color = Color_Combo_Data_4d2900(dialog, 0x6A2, -1);
        unknown_session_a3d298.Set_Value_00672ae0(local_color, true);
        NodeNameType *node = new NodeNameType;
        if (node) {
            wcscpy(node->Name, Unknown_006FA180(unknown_session_a3d298.Handle));
            node->unknown_4b = unknown_session_a3d298.unknown_124;
            node->unknown_53 = unknown_session_a3d298.unknown_11c;
            node->unknown_63 = -1;
            unknown_session_a3d298.Players.Add(node);
        }
        unknown_session_a3d298.Unknown_00672BB0();
        HWND item = Get_Item(dialog, 0x529);
        if (item) {
            unknown_a40b18 = unknown_session_a3d298.GameSpeed_30 = 6 - SendMessageA(item, 0x400, 0, 0);
        }
        item = Get_Item(dialog, 0x511);
        if (item) {
            unknown_session_a3d298.unknown_24 = SendMessageA(item, 0x400, 0, 0);
        }
        item = Get_Item(dialog, 0x50C);
        if (item) {
            unknown_session_a3d298.UnitCount = SendMessageA(item, 0x400, 0, 0);
        }
        unknown_session_a3d298.SkirmishOptions.GameSpeed = unknown_session_a3d298.GameSpeed_30;
        unknown_session_a3d298.SkirmishOptions.Credits = unknown_session_a3d298.unknown_24;
        unknown_session_a3d298.SkirmishOptions.UnitCount = unknown_session_a3d298.UnitCount;
        item = Get_Item(dialog, 0x54E);
        if (item) {
            unknown_session_a3d298.unknown_2a = SendMessageA(item, 0xF0, 0, 0) == 1;
        }
        item = Get_Item(dialog, 0x69A);
        if (item) {
            unknown_session_a3d298.unknown_2b = SendMessageA(item, 0xF0, 0, 0) == 1;
        }
        item = Get_Item(dialog, 0x69D);
        if (item) {
            unknown_session_a3d298.unknown_2c = SendMessageA(item, 0xF0, 0, 0) == 1;
        }
        item = Get_Item(dialog, 0x693);
        if (item) {
            unknown_session_a3d298.unknown_a8 = SendMessageA(item, 0xF0, 0, 0) == 1;
        }
        item = Get_Item(dialog, 0x696);
        if (item) {
            unknown_session_a3d298.unknown_crates_29 = SendMessageA(item, 0xF0, 0, 0) == 1;
        }
        unknown_session_a3d298.SkirmishOptions.ShortGame = unknown_session_a3d298.unknown_2a;
        unknown_session_a3d298.SkirmishOptions.SuperWeaponsAllowed = unknown_session_a3d298.unknown_2b;
        unknown_session_a3d298.SkirmishOptions.BuildOffAlly = unknown_session_a3d298.unknown_2c;
        unknown_session_a3d298.SkirmishOptions.MCVRepacks = unknown_session_a3d298.unknown_a8;
        unknown_session_a3d298.SkirmishOptions.CratesAppear = unknown_session_a3d298.unknown_crates_29;
        unknown_session_a3d298.unknown_fog_a7 = false;
        unknown_session_a3d298.unknown_28 = true;
        unknown_session_a3d298.unknown_a5 = false;
        unknown_session_a3d298.unknown_34 = false;
        if (unknown_dialog_preview_a72ce8) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8 = 0;
        }
        *result = id;
        return;
    }
    case 0x510:
    case 0x513:
    case 0x514:
    case 0x51E:
    case 0x51F:
    case 0x520:
    case 0x521:
    case 0x6A1:
        Show_Player_Flag_4d1230(dialog, Side_Combo_Player_4d13b0(id));
        break;
    case 0x522:
    case 0x523:
    case 0x524:
    case 0x525:
    case 0x526:
    case 0x527:
    case 0x528:
    case 0x6A2:
        if (code == 1) {
            Color_Combo_Changed_4d2700(dialog, id);
        }
        break;
    }
}
