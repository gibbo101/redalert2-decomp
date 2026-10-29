// @ref ?DialogStack@@3PAUDialogStackEntry@@A=00b25bb8
// @ref ?CurrentDialog@@3PAUHWND__@@A=00b25dd4
// @ref ?CurrentDialogResource@@3HA=00b25dd8
// @ref ?DialogStackCount@@3HA=00b25de0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref ?unknown_5e5fc0@OwnerDraw@@YI_NPAUHWND__@@@Z=005e5fc0
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/keyboard.hpp"
#include "shared/crt_memory.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"

// Clears the keyboard buffer, destroys a dialog and removes it from the dialog stack; the new top
// (or the main window) becomes the foreground window with the focus (0x005FF6E0).
void __fastcall unknown_dialog_5ff6e0(HWND window)
{
    WWKeyboard->Clear();
    OwnerDraw::unknown_5e5fc0(window);
    DestroyWindow(window);
    for (int index = 0; index < DialogStackCount; index++) {
        if (DialogStack[index].Window == window) {
            memmove(&DialogStack[index], &DialogStack[index + 1], (DialogStackCount - (index + 1)) * sizeof(DialogStackEntry));
            DialogStack[DialogStackCount - 1].Window = 0;
            DialogStack[DialogStackCount - 1].Resource = 0;
            DialogStackCount--;
            if (DialogStackCount > 0) {
                CurrentDialog = DialogStack[DialogStackCount - 1].Window;
                CurrentDialogResource = DialogStack[DialogStackCount - 1].Resource;
                SetForegroundWindow(CurrentDialog);
                SetFocus(CurrentDialog);
            } else {
                CurrentDialog = 0;
                CurrentDialogResource = 0;
                SetForegroundWindow(MainWindow);
                SetFocus(MainWindow);
            }
            return;
        }
    }
}
