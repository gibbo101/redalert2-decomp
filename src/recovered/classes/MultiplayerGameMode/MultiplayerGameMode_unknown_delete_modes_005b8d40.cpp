// void MultiplayerGameMode::unknown_delete_modes_5b8d40() -- 0x005B8D40
// Deletes every registered game mode (the list accessor is expanded inline
// twice per iteration).

void MultiplayerGameMode::unknown_delete_modes_5b8d40()
{
    for (int index = 0; index < unknown_modes_5b6c30().Count(); index++) {
        delete unknown_modes_5b6c30()[index];
    }
}
