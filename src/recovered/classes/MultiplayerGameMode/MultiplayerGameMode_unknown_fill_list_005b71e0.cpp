// void MultiplayerGameMode::unknown_fill_list_5b71e0(HWND list, int id) -- 0x005B71E0
// The list-box twin of 0x005B70B0 with two more filters.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref ?unknown_text_770430@WideString@@QBEPBGXZ=00770430
// @ref ?unknown_73c370@@YA_NXZ=0073c370
#include "shared/multiplayer_game_mode.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/lobby.hpp"
#include "shared/network_tests.hpp"
#include "shared/unknown_player_entry.hpp"

void __fastcall MultiplayerGameMode::unknown_fill_list_5b71e0(HWND list, int id)
{
    SendMessageA(list, 0x184, 0, 0);
    bool listed = unknown_game_mode_a3d298 == 5;
    for (int index = 0; index < unknown_mode_count_5b6f80(); index++) {
        MultiplayerGameMode *mode = unknown_modes_5b6c30()[index];
        if (mode->unknown_3c == 0 && unknown_game_mode_a3d298 == 4 && unknown_73c370()) {
            continue;
        }
        if (unknown_lobby_flag_7e6d90 == 0 && unknown_player_slots_a3fa98[0]->Team == -1 && !mode->unknown_slot40()) {
            continue;
        }
        if (!listed || mode->unknown_slot12()) {
            int item = SendMessageA(list, 0x4CD, 0, (LPARAM)mode->Get_Name().unknown_text_770430());
            if (mode->Get_ID() == id) {
                SendMessageA(list, 0x186, item, 0);
            }
            SendMessageA(list, 0x19A, item, (LPARAM)mode);
        }
    }
}
