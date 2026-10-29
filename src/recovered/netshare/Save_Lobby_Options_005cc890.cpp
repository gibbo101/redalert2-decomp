// void __fastcall Save_Lobby_Options_005cc890(HWND dialog, UnknownGameOptions *options) (0x005CC890)
// Copies the session's game settings and each slot's entry kind, side and colour (read from the lobby
// dialog's combo boxes) into a per-game-type settings block.
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"

void __fastcall Save_Lobby_Options_005cc890(HWND dialog, UnknownGameOptions *options)
{
    options->GameMode = unknown_session_a3d298.GameModeIndex;
    options->ScenIndex = unknown_session_a3d298.ScenarioIndex;
    for (int slot = 1; slot < 8; slot++) {
        int id = Slot_Control_Id_005c97a0(slot);
        int index = SendDlgItemMessageA(dialog, id, 0x147, 0, 0);
        int data = SendDlgItemMessageA(dialog, id, 0x150, index, 0);
        options->Slots[slot][0] = Entry_Kind_005c9650((NodeNameType *)(data == -1 ? 0 : data));
        int side_id = Player_Side_Combo_ID_4d1350(slot);
        options->Slots[slot][1] = Side_Combo_Data_4d1c70(dialog, side_id, -1);
        int color_id = Player_Color_Combo_ID_4d1cb0(slot);
        options->Slots[slot][2] = Color_Combo_Data_4d2900(dialog, color_id, -1);
    }
    options->GameSpeed = unknown_session_a3d298.GameSpeed_30;
    options->Credits = unknown_session_a3d298.unknown_24;
    options->UnitCount = unknown_session_a3d298.UnitCount;
    options->ShortGame = unknown_session_a3d298.unknown_2a;
    options->SuperWeaponsAllowed = unknown_session_a3d298.unknown_2b;
    options->BuildOffAlly = unknown_session_a3d298.unknown_2c;
    options->MCVRepacks = unknown_session_a3d298.unknown_a8;
    options->CratesAppear = unknown_session_a3d298.unknown_crates_29;
}
