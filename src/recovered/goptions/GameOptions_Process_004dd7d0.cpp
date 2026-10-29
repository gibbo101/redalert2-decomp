// void Unknown_004DD7D0() (0x004DD7D0): the in-game options menu (Red Alert's GameOptionsClass::Process).
#include "shared/house.hpp"         // ahead of map_view.hpp: after it, Houses.Count() and operator[] stay out of line in Game_Options_Proc
#include "shared/game_options_dialog.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ?Options_Menu_Proc@@YGHPAUHWND__@@IIJ@Z=004dd8a0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?Unknown_0063B090@@YIXPAVUnknownIDSource@@@Z=0063b090
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

void __fastcall Unknown_0063B090(UnknownIDSource *scenario);    // 0x0063B090

void Unknown_004DD7D0()
{
    int result = 0;
    HWND window;
    if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5) {
        window = unknown_create_dialog_5ff610(0xB5, Options_Menu_Proc, 0);
    } else if (unknown_game_mode_a3d298 == 4) {
        if (unknown_int_a3d548) {
            window = unknown_create_dialog_5ff610(0xBBA, Options_Menu_Proc, 0);
        } else {
            window = unknown_create_dialog_5ff610(0xFF, Options_Menu_Proc, 0);
        }
    } else {
        window = unknown_create_dialog_5ff610(0xBBA, Options_Menu_Proc, 0);
    }
    if (window) {
        SetWindowLongA(window, 8, (LONG)&result);
        unknown_dialog_5ff7c0(window);
        while (!result) {
            if (unknown_6000d0() == true) {
                result = 1;
            }
        }
        unknown_dialog_5ff6e0(window);
    }
    if (result == 0x3EC) {
        Unknown_0063B090(unknown_id_source_a3d290);
    }
    Map.Flag_To_Redraw(2);
}
