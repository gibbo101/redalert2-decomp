// void MultiplayerGameMode::unknown_fill_combo_5b70b0(HWND combo, int id) -- 0x005B70B0
// Fills a combo box with the registered modes' names (each mode as item data) and selects the mode
// whose id matches; in game mode 5 only the modes whose slot 12 agrees are listed.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref ?unknown_reset_combo_6007f0@@YIXPAUHWND__@@@Z=006007f0
// @ref ?unknown_text_770430@WideString@@QBEPBGXZ=00770430
#include "shared/multiplayer_game_mode.hpp"
#include "shared/unknown_globals.hpp"

void __fastcall MultiplayerGameMode::unknown_fill_combo_5b70b0(HWND combo, int id)
{
    unknown_reset_combo_6007f0(combo);
    bool listed = unknown_game_mode_a3d298 == 5;
    for (int index = 0; index < unknown_mode_count_5b6f80(); index++) {
        MultiplayerGameMode *mode = unknown_modes_5b6c30()[index];
        if (!listed || mode->unknown_slot12()) {
            int item = SendMessageA(combo, 0x143, 0, (LPARAM)mode->Get_Name().unknown_text_770430());
            if (mode->Get_ID() == id) {
                SendMessageA(combo, 0x14E, item, 0);
            }
            SendMessageA(combo, 0x151, item, (LPARAM)mode);
        }
    }
}
