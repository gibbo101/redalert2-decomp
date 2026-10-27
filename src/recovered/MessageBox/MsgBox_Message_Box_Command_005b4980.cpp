// void __fastcall Message_Box_Command(HWND window, int id, HWND control, unsigned code) (0x005B4980)
// WM_COMMAND of the message box: stores the pressed button's result through
// the DWL_USER pointer (0x5AE: 0, IDOK/IDCANCEL: 1, 0x5AF: 2). Expanded into
// Message_Box_Proc; this out-of-line copy has no callers.
#include "shared/ms_message_box.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c

void __fastcall Message_Box_Command(HWND window, int id, HWND control, unsigned code)
{
    int *result = (int *)GetWindowLongA(window, 8);
    switch (id) {
        case 1:
        case 2:
            if (code == 0) {
                *result = 1;
            }
            break;
        case 0x5AE:
            if (code == 0) {
                *result = 0;
            }
            break;
        case 0x5AF:
            if (code == 0) {
                *result = 2;
            }
            break;
    }
}
