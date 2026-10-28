// bool MPCooperative::unknown_slot26() -- 0x005A3EE0
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/string_table.hpp"
#include "shared/lobby.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?Get_Lobby_Dialog_005c2c40@@YAPAUHWND__@@XZ=005c2c40
// @ref __imp__ShowWindow@8=0079a498
// @ref ??_C@_0BA@FFI@NAME?3COOPDESC?$CFd?$AA@=007e34f8
// @ref ??_C@_0BC@DFJB@D?3?2Ra2?2MPCoop?4cpp?$AA@=007e34e4
bool MPCooperative::unknown_slot26()
{
    HWND dialog = Get_Lobby_Dialog_005c2c40();
    if (dialog != 0 && unknown_campaign_44 != 0) {
        int campaign;
        if (unknown_campaign_44->Get_Campaign_Type_0048e6b0(&campaign)) {
            char label[64];
            sprintf(label, "NAME:COOPDESC%d", campaign + 1);
            HWND item = GetDlgItem(dialog, 0x72F);
            if (item != 0) {
                SendMessageA(item, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\MPCoop.cpp", 0x31E));
                ShowWindow(item, SW_SHOW);
            }
        }
    }
    return true;
}
