// BOOL __fastcall Skirmish_Is_Computer(HWND dialog, int id) (0x006836B0)
// Whether the player-type combo box `id` selects a computer player (type 0-2).
#include "shared/skirmish.hpp"

BOOL __fastcall Skirmish_Is_Computer(HWND dialog, int id)
{
    int selection = SendDlgItemMessageA(dialog, id, CB_GETCURSEL, 0, 0);
    int type = SendDlgItemMessageA(dialog, id, CB_GETITEMDATA, selection, 0);
    if (type != 0 && type != 1 && type != 2) {
        return FALSE;
    }
    return TRUE;
}
