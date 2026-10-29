// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
#include "shared/win32_api.hpp"
#include "shared/keyboard.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"

// Shows a window, brings it to the foreground and clears the keyboard buffer (0x005FF7C0).
void __fastcall unknown_dialog_5ff7c0(HWND window)
{
    ShowWindow(window, SW_SHOWNORMAL);
    SetForegroundWindow(window);
    WWKeyboard->Clear();
}
