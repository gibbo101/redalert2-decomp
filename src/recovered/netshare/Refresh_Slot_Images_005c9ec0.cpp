// void __fastcall Refresh_Slot_Images_005c9ec0(HWND dialog) (0x005C9EC0)
#include "shared/lobby.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/owner_draw_dialog_control.hpp"
// @ref ?unknown_host_image_7e6db8@@3PBDB=007e6db8
// @ref ?unknown_accept_image_7e6dbc@@3PBDB=007e6dbc
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

void __fastcall Refresh_Slot_Images_005c9ec0(HWND dialog)
{
    for (int i = 0; i < 8; i++) {
        HWND control = GetDlgItem(dialog, Slot_Color_Control_Id_005ca4e0(i));
        Surface *image = 0;
        if (Is_Player_Entry(unknown_player_slots_a3fa98[i]) && unknown_player_slots_a3fa98[i] != unknown_easy_ai_entry_a72d34
            && unknown_player_slots_a3fa98[i] != unknown_medium_ai_entry_a72d38
            && unknown_player_slots_a3fa98[i] != unknown_hard_ai_entry_a72d3c
            && Compare_Wide_007837d3(unknown_player_slots_a3fa98[i]->Name, unknown_host_name_a3f618) == 0) {
            image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_host_image_7e6db8, 0);
        } else if ((unknown_player_slots_a3fa98[i] != 0 && (unknown_player_slots_a3fa98[i] == unknown_easy_ai_entry_a72d34
                    || unknown_player_slots_a3fa98[i] == unknown_medium_ai_entry_a72d38
                    || unknown_player_slots_a3fa98[i] == unknown_hard_ai_entry_a72d3c))
                   || unknown_player_slots_a3fa98[i]->unknown_67 == 1) {
            image = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_accept_image_7e6dbc, 0);
        }
        OwnerDraw::unknown_5e1f30(control, image);
    }
}
