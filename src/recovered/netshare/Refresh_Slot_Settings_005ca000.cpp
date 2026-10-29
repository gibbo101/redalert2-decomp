// void __fastcall Refresh_Slot_Settings_005ca000(HWND dialog, bool full) (0x005CA000)
// Refreshes the lobby dialog's slot controls. With full set it rebuilds the slot rows (0x005CA6C0) and
// redoes every country flag, side and colour combo box; otherwise it redoes the status images and only
// what changed since the last call: the slot names (rows rebuilt), the countries and the colours, each
// compared as a text list.
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/progress_screen.hpp"
// @ref ?Unknown_005ca6c0@@YIXPAUHWND__@@@Z=005ca6c0
// @ref ?Unknown_0075b0c0@@YAXXZ=0075b0c0
// @ref ??_C@_03NBMA@?$CFd?0?$AA@=007e6ed4
// @ref ?unknown_slot_names_a72734@@3PAGA=00a72734
// @ref ?unknown_slot_names_old_a728e4@@3PAGA=00a728e4

// The slots' country flags and side combo boxes (helpers with no out-of-line copy: both expansions in
// 0x005CA000 are identical).
static void Refresh_Country_Flags(HWND dialog)
{
    for (int i = 0; i < 8; i++) {
        HWND control = GetDlgItem(dialog, unknown_player_control_4d0ee0(i));
        OwnerDraw::unknown_5e1f30(control, Country_Flag_004d1120(Slot_Country_005ca3f0(i)));
    }
}

static void Refresh_Side_Combos(HWND dialog)
{
    for (int i = 0; i < 8; i++) {
        int id = Player_Side_Combo_ID_4d1350(i);
        Select_Side_Combo_4d1a90(dialog, id, Slot_Country_005ca3f0(i));
    }
}

static bool Slot_Names_Changed()
{
    wcscpy(unknown_slot_names_old_a728e4, unknown_slot_names_a72734);
    Unknown_Slot_Names_005c8cf0(unknown_slot_names_a72734);
    return Compare_Wide_007837d3(unknown_slot_names_old_a728e4, unknown_slot_names_a72734) != 0;
}

static bool Country_List_Changed()
{
    char text[4];
    strcpy(unknown_country_list_old_a72a44, unknown_country_list_a726f8);
    unknown_country_list_a726f8[0] = 0;
    for (int i = 0; i < 8; i++) {
        sprintf(text, "%d,", Slot_Country_005ca3f0(i));
        strcat(unknown_country_list_a726f8, text);
    }
    return strcmp(unknown_country_list_old_a72a44, unknown_country_list_a726f8) != 0;
}

static bool Color_List_Changed()
{
    char text[4];
    strcpy(unknown_color_list_old_a726b0, unknown_color_list_a726d4);
    unknown_color_list_a726d4[0] = 0;
    for (int i = 0; i < 8; i++) {
        sprintf(text, "%d,", Slot_Color_005ca480(i));
        strcat(unknown_color_list_a726d4, text);
    }
    return strcmp(unknown_color_list_old_a726b0, unknown_color_list_a726d4) != 0;
}

void __fastcall Refresh_Slot_Settings_005ca000(HWND dialog, bool full)
{
    if (full) {
        Unknown_005ca6c0(dialog);
        Refresh_Country_Flags(dialog);
        Refresh_Side_Combos(dialog);
        Refresh_Slot_Colors_005ca540(dialog);
        if (unknown_game_mode_a3d298 == 4) {
            Unknown_0075b0c0();
        }
        return;
    }
    for (int slot = 0; slot < 8; slot++) {
        Refresh_Slot_Image(dialog, slot);
    }
    if (Slot_Names_Changed()) {
        Unknown_005ca6c0(dialog);
        if (unknown_game_mode_a3d298 == 4) {
            Unknown_0075b0c0();
        }
    }
    Refresh_Country_Flags(dialog);
    if (Country_List_Changed()) {
        Refresh_Side_Combos(dialog);
    }
    if (Color_List_Changed()) {
        Refresh_Slot_Colors_005ca540(dialog);
    }
}
