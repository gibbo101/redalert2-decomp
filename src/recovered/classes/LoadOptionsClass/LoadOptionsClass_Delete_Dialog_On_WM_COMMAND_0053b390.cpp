// Records how the player left the delete dialog (0x0053B390).
#include "shared/load_dlg.hpp"

void __fastcall LoadOptionsClass::Delete_Dialog_On_WM_COMMAND(HWND window, int id, HWND control, int code)
{
    LoadOptionsClass *options = (LoadOptionsClass *)GetWindowLongA(window, 8);
    switch (id) {
    case 0x686:
        if (code == 0) {
            options->State = 2;
        }
        break;
    case 0x6c8:
        if (code == 0) {
            options->State = 1;
        }
        break;
    }
}
