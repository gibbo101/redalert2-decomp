// @ref __imp__RegisterClassA@4=0079a4cc
// @ref ??_C@_0N@DOOI@ComboDropWin?$AA@=007eacf8
// @ref ??_C@_07FHL@NewEdit?$AA@=007e8de8
// @ref ?ProgramInstance@@3PAXA=00b26180
// @ref ?unknown_classes_registered_a763f0@OwnerDraw@@3HA=00a763f0
// @ref ?unknown_combo_drop_proc_5ead20@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005ead20
// @ref ?unknown_new_edit_proc_5ead00@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005ead00
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"
#include "shared/win32_window.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Registers the "ComboDropWin" and "NewEdit" window classes once.
void __fastcall unknown_5eac30()
{
    if (unknown_classes_registered_a763f0 == 1) {
        return;
    }
    unknown_classes_registered_a763f0 = 1;
    WNDCLASSA window_class;
    memset(&window_class, 0, sizeof(window_class));
    window_class.hInstance = ProgramInstance;
    window_class.style = 3;
    window_class.lpfnWndProc = unknown_combo_drop_proc_5ead20;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hIcon = 0;
    window_class.hCursor = 0;
    window_class.hbrBackground = 0;
    window_class.lpszMenuName = "ComboDropWin";
    window_class.lpszClassName = "ComboDropWin";
    RegisterClassA(&window_class);
    memset(&window_class, 0, sizeof(window_class));
    window_class.style = 0x83;
    window_class.lpfnWndProc = unknown_new_edit_proc_5ead00;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = ProgramInstance;
    window_class.hIcon = 0;
    window_class.hCursor = 0;
    window_class.hbrBackground = 0;
    window_class.lpszMenuName = 0;
    window_class.lpszClassName = "NewEdit";
    RegisterClassA(&window_class);
}

}
