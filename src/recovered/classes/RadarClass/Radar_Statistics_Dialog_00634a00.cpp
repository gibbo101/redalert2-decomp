// void __fastcall Unknown_00634A00(MouseClass *map) (0x00634A00)
// Shows dialog 0x73 (procedure 0x006340F0) with input held off, waits until
// it sets its result or the game quits (0x423), then restores the input flag
// from the pause state and redraws the map.
#include "shared/radar.hpp"
#include "shared/dialog_create.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/keyboard.hpp"
#include "shared/id_source.hpp"
#include "shared/mouse.hpp"
#include "shared/map_view.hpp"
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?Unknown_006340F0@@YGHPAUHWND__@@IIJ@Z=006340f0


void __fastcall Unknown_00634A00(MouseClass *map)
{
    HWND window = unknown_create_dialog_5ff610(0x73, Unknown_006340F0, 0);
    unknown_flag_a40d44 = true;
    WWKeyboard->Clear();
    if (window) {
        int result;
        SetWindowLongA(window, 8, (LONG)&result);
        unknown_dialog_5ff7c0(window);
        result = 0;
        while (true) {
            if (unknown_6000d0()) {
                result = 0x423;
                break;
            }
            if (result) {
                break;
            }
        }
        unknown_dialog_5ff6e0(window);
    }
    WWKeyboard->Clear();
    unknown_flag_a40d44 = unknown_id_source_a3d290->unknown_2306;
    Map.Flag_To_Redraw(2);
}
