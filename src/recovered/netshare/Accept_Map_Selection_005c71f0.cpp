// bool Accept_Map_Selection_005c71f0(HWND dialog) (0x005C71F0)
// Takes the map (list 0x553) and the game mode (list 0x6EB) the lobby dialog selects. When the
// map has fewer players than the lobby holds, the game mode's test (0x005BC430, 0x0075CA30 or
// Skirmish_Has_Computer_After) may ask first (GUI:EjectPlayers / GUI:EjectAIPlayers): Ok goes on,
// Cancel keeps the old settings. The new mode replaces the old one (slot 33 releases it, slot 8
// sets it up), the dialog ends with 1 and the setup dialog's mode and map controls (0x6EC and
// 0x5A8 of dialog 0xC2, 0xC9, 0xBC or 0xBD) take the new choice.
#include "shared/lobby.hpp"
#include "shared/multi_mission.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/skirmish.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/win32_api.hpp"
// @ref ??_C@_06IFDN@GUI?3Ok?$AA@=007dbc48
// @ref ??_C@_0BB@HHL@GUI?3EjectPlayers?$AA@=007e70e4
// @ref ??_C@_0BD@MOPA@GUI?3EjectAIPlayers?$AA@=007e70d0
// @ref ??_C@_0L@EJFF@GUI?3Cancel?$AA@=007d1604
// @ref ?Unknown_005bc430@@YI_NH_N0@Z=005bc430
// @ref ?unknown_dialog_c2_call@@YI_NH_N0@Z=0075ca30

bool __fastcall unknown_dialog_c2_call(int players, bool unknown_1, bool unknown_2);
bool __fastcall Accept_Map_Selection_005c71f0(HWND dialog);

bool __fastcall Accept_Map_Selection_005c71f0(HWND dialog)
{
    int item = Selected_Campaign_005c67a0();
    int index = -1;
    if (item != -1) {
        MultiMission *map = (MultiMission *)SendDlgItemMessageA(unknown_lobby_dialog_a728e0, 0x553, 0x199, item, 0);   // LB_GETITEMDATA
        for (int i = 0; i < unknown_session_a3d298.Scenarios.Count(); i++) {
            if (map == unknown_session_a3d298.Scenarios[i]) {
                index = i;
                break;
            }
        }
    }
    if (index == -1) {
        return false;
    }
    MultiplayerGameMode *old_mode = unknown_session_a3d298.Mode;
    HWND lobby = unknown_lobby_dialog_a728e0;
    MultiplayerGameMode *mode = 0;
    int selected = SendDlgItemMessageA(unknown_lobby_dialog_a728e0, 0x6EB, 0x188, 0, 0);
    if (selected != -1) {
        mode = (MultiplayerGameMode *)SendDlgItemMessageA(lobby, 0x6EB, 0x199, selected, 0);
    }
    unknown_session_a3d298.Mode = mode;
    bool unknown2 = mode->unknown_slot12();
    bool unknown3 = mode->unknown_slot40();
    int players = Unknown_005c6600(index);
    if (unknown_session_a3d298.Mode != 0) {
        int limit = unknown_session_a3d298.Mode->unknown_slot32();
        if (limit != -1 && limit < players) {
            players = limit;
        }
    }
    if (unknown_game_mode_a3d298 == 4) {
        if (unknown_73c3a0()) {
            players &= ~1;
        } else if (unknown_73c370()) {
            players = 2;
        }
    }
    unknown_session_a3d298.Mode = old_mode;
    bool computers = false;
    bool ask;
    switch (unknown_game_mode_a3d298) {
    case 3:
        ask = Unknown_005bc430(players, unknown2, unknown3);
        break;
    case 4:
        ask = unknown_dialog_c2_call(players, unknown2, unknown3);
        break;
    case 5:
        ask = Skirmish_Has_Computer_After(players);
        computers = true;
        break;
    default:
        ask = false;
        break;
    }
    if (ask) {
        unsigned short const *text = StringTable::Load_String(!computers ? "GUI:EjectPlayers" : "GUI:EjectAIPlayers", 0, "D:\\Ra2\\netshare.cpp", 0xA5F);
        unsigned short const *ok = StringTable::Load_String("GUI:Ok", 0, "D:\\Ra2\\netshare.cpp", 0xA60);
        unsigned short const *cancel = StringTable::Load_String("GUI:Cancel", 0, "D:\\Ra2\\netshare.cpp", 0xA61);
        if (WWMessageBox(L" ").Process(text, ok, cancel, 0, false)) {
            return false;
        }
    }
    if (mode != unknown_session_a3d298.Mode) {
        if (unknown_session_a3d298.Mode != 0) {
            unknown_session_a3d298.Mode->unknown_slot33();
        }
        if (mode != 0) {
            unknown_session_a3d298.Mode = mode;
            unknown_session_a3d298.GameModeIndex = mode->Get_ID();
            unknown_session_a3d298.ScenarioIndex = index;
            mode->unknown_slot8();
        }
    }
    unknown_session_a3d298.ScenarioIndex = index;
    if (mode != 0) {
        mode->unknown_slot9();
    }
    mode->unknown_slot6();
    mode->unknown_slot26();
    Unknown_007357E0(dialog, 1);
    HWND setup = Find_Dialog_00735940(0xC2);
    if (setup == 0) {
        setup = Find_Dialog_00735940(0xC9);
        if (setup == 0) {
            setup = Find_Dialog_00735940(0xBC);
            if (setup == 0) {
                setup = Find_Dialog_00735940(0xBD);
            }
        }
    }
    HWND control = GetDlgItem(setup, 0x6EC);
    SendMessageA(control, 0x4B2, 0, (LPARAM)mode->Get_Name().unknown_text_770430());
    MultiMission *current = unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex];
    control = GetDlgItem(setup, 0x5A8);
    SendMessageA(control, 0x4B2, 0, (LPARAM)current);
    mode->unknown_slot20();
    return true;
}
