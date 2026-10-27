// void MultiplayerGameMode::unknown_slot16(HWND combo, int player) -- 0x005B75D0
// Slot 16: rebuilds the teams (slot 41), then fills a team combo box (reset
// by 0x006007F0) with every team's name, keeps the team as item data and
// selects the team of the given player (a valid player list index).
// @ref ?unknown_reset_combo_6007f0@@YIXPAUHWND__@@@Z=006007f0
// @ref ?unknown_text_770430@WideString@@QBEPBGXZ=00770430

void MultiplayerGameMode::unknown_slot16(HWND combo, int player)
{
    unknown_reset_combo_6007f0(combo);
    for (int index = 0; index < Teams.Count(); index++) {
        delete Teams[index];
    }
    Teams.Clear();
    unknown_slot41(&Teams);
    if (player >= 0 && player < unknown_players_a3fa7c.Count()) {
        player = unknown_players_a3fa7c[player]->Team;
        for (int team_index = 0; team_index < Teams.Count(); team_index++) {
            MultiplayerTeam *team = Teams[team_index];
            int item = SendMessageA(combo, 0x143, 0, (long)team->Name.unknown_text_770430());   // CB_ADDSTRING
            if (team->Number == player) {
                SendMessageA(combo, 0x14e, item, 0);                                       // CB_SETCURSEL
            }
            SendMessageA(combo, 0x151, item, (long)team);                                  // CB_SETITEMDATA
        }
    }
}
