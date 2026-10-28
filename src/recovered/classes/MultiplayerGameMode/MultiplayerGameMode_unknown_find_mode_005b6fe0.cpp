// MultiplayerGameMode *MultiplayerGameMode::unknown_find_mode_5b6fe0(int id) -- 0x005B6FE0
// @ref ??0?$VectorClass@PAVMultiplayerGameMode@@@@QAE@IPBQAVMultiplayerGameMode@@@Z=005b98e0

MultiplayerGameMode *__fastcall MultiplayerGameMode::unknown_find_mode_5b6fe0(int id)
{
    for (int index = 0; index < unknown_mode_count_5b6f80(); index++) {
        MultiplayerGameMode *mode = unknown_modes_5b6c30()[index];
        if (mode->unknown_28 == id) {
            return mode;
        }
    }
    return 0;
}
