// int WWMessageBox::Process(unsigned short const *text, unsigned short const *button1,
//     unsigned short const *button2, unsigned short const *button3, bool unknown5) (0x005B46B0)
// Shows the message box dialog (0xCE, 0x120 with a second, 0x121 with a
// third button), waits for a button and restores the mouse hide count.
#include "shared/ms_message_box.hpp"

int WWMessageBox::Process(unsigned short const *text, unsigned short const *button1,
                          unsigned short const *button2, unsigned short const *button3, bool unknown5)
{
    int result = -1;
    int buttons = 0;
    int state = WWMouse->Get_Mouse_State();
    bool has_text = text != 0 && *text != 0;
    bool has_button1 = button1 != 0 && *button1 != 0;
    bool has_button2 = button2 != 0 && *button2 != 0;
    bool has_button3 = button3 != 0 && *button3 != 0;
    unknown_5159b0(0, true);

    int resource = 0xCE;
    if (has_button3) {
        resource = 0x121;
    } else if (has_button2) {
        resource = 0x120;
    }
    HWND dialog = unknown_create_dialog_5ff610(resource, Message_Box_Proc, 0);
    if (dialog != 0) {
        SetWindowLongA(dialog, 8, (LONG)&result);
        if (has_text) {
            HWND control = GetDlgItem(dialog, 0x5B0);
            SendMessageA(control, 0x4B2, 0, (LPARAM)text);
        }
        if (has_button1) {
            HWND control = GetDlgItem(dialog, 0x5AE);
            SendMessageA(control, 0x4B2, 0, (LPARAM)button1);
            buttons = 1;
        }
        if (has_button2) {
            HWND control = GetDlgItem(dialog, 2);
            SendMessageA(control, 0x4B2, 0, (LPARAM)button2);
            buttons = 2;
        }
        if (has_button3) {
            HWND control = GetDlgItem(dialog, 0x5AF);
            SendMessageA(control, 0x4B2, 0, (LPARAM)button3);
            buttons = 3;
        }
        unknown_dialog_5ff7c0(dialog);
        if (buttons > 0) {
            while (WWMouse->Get_Mouse_State() != 0) {
                WWMouse->Show_Mouse();
            }
            while (result < 0) {
                if (unknown_6000d0()) {
                    break;
                }
                if (!unknown_flag_a40958) {
                    unknown_517370(false);
                }
            }
        } else {
            result = 0;
        }
        unknown_dialog_5ff6e0(dialog);
    }
    while (state < WWMouse->Get_Mouse_State()) {
        WWMouse->Hide_Mouse();
    }
    return result;
}
