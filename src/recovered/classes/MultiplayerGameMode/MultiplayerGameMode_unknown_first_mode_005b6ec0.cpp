// MultiplayerGameMode *MultiplayerGameMode::unknown_first_mode_5b6ec0() -- 0x005B6EC0

MultiplayerGameMode *MultiplayerGameMode::unknown_first_mode_5b6ec0()
{
    if (unknown_modes_5b6c30().Count() == 0) {
        return 0;
    }
    return unknown_modes_5b6c30()[0];
}
