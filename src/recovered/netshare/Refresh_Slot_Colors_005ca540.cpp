// void __fastcall Refresh_Slot_Colors_005ca540(HWND dialog) (0x005CA540)
// Selects every slot's colour in its colour combo box, the local player's first.
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"

void __fastcall Refresh_Slot_Colors_005ca540(HWND dialog)
{
    int own = Find_First_Player_Slot_005c8c70();
    if (own != -1) {
        int id = Player_Color_Combo_ID_4d1cb0(own);
        Select_Color_Combo_4d2480(dialog, id, Slot_Color_005ca480(own));
    }
    for (int i = 0; i < 8; i++) {
        if (i != own) {
            int id = Player_Color_Combo_ID_4d1cb0(i);
            Select_Color_Combo_4d2480(dialog, id, Slot_Color_005ca480(i));
        }
    }
}
