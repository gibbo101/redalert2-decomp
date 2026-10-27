// void FreeForAll::unknown_slot16(HWND combo, int team) -- 0x005A7150
// Slot 16: resets a team combo box (0x006007F0), lets team `team` and team
// -1 add their entries (0x005B9BE0) and selects the first entry.
#include "shared/win32_api.hpp"
// @ref ?unknown_reset_combo_6007f0@@YIXPAUHWND__@@@Z=006007f0
// @ref ?unknown_find_team_5b76b0@MultiplayerGameMode@@QAEPAVMultiplayerTeam@@H@Z=005b76b0
// @ref ?unknown_add_to_combo_5b9be0@MultiplayerTeam@@QAEHPAUHWND__@@@Z=005b9be0
// @ref __imp__SendMessageA@16=0079a4a0

WIN32_IMPORT long __stdcall SendMessageA(HWND window, unsigned int message, unsigned int wparam, long lparam);
void __fastcall unknown_reset_combo_6007f0(HWND combo);

void FreeForAll::unknown_slot16(HWND combo, int team)
{
    unknown_reset_combo_6007f0(combo);
    MultiplayerTeam *entry = unknown_find_team_5b76b0(team);
    if (entry != 0) {
        entry->unknown_add_to_combo_5b9be0(combo);
    }
    entry = unknown_find_team_5b76b0(-1);
    if (entry != 0) {
        entry->unknown_add_to_combo_5b9be0(combo);
    }
    SendMessageA(combo, 0x14e, 0, 0);    // CB_SETCURSEL
}
