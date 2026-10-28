// bool __fastcall Skirmish_Has_Computer_After(int player) (0x00682930)
// Whether any player from `player` to 7 is a computer player.
#include "shared/skirmish.hpp"

bool __fastcall Skirmish_Has_Computer_After(int player)
{
    HWND dialog = SkirmishDialog;
    for (int index = player; index < 8; index++) {
        if (Skirmish_Is_Computer(dialog, Skirmish_Player_Combo_ID(index - 1))) {
            return true;
        }
    }
    return false;
}

// @ref ?SkirmishDialog@@3PAUHWND__@@A=00abcdfc
