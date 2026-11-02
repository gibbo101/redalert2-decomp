// Records how the player left the load dialog (0x0053B200).
#include "shared/load_dlg.hpp"

void __fastcall LoadOptionsClass::Load_Dialog_On_WM_COMMAND(HWND window, int id, HWND control, int code)
{
    LoadOptionsClass *options = (LoadOptionsClass *)GetWindowLongA(window, 8);
    switch (id) {
    case 0x525:
        if (code == 2 && SendMessageA(control, 0x18b, 0, 0) > 0) {
            options->State = 0x40f;
        }
        break;
    case 0x40f:
        if (code == 0) {
            options->State = id;
        }
        break;
    case 0x686:
        options->State = 2;
        break;
    }
}
