// @ref __imp__GetClassNameA@12=0079a4e0
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref ??_C@_04EDLP@Edit?$AA@=007e8df0
// @ref ??_C@_07FHL@NewEdit?$AA@=007e8de8
// @ref ??_C@_07NOMM@ListBox?$AA@=007e8de0
// @ref ??_C@_08EIKH@ComboBox?$AA@=007e8dd4
#include "shared/win32_api.hpp"
#include "shared/crt_string.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

int __fastcall unknown_5e1ca0(HWND dialog, HWND window)
{
    UnknownControlRecord *record = 0;
    unknown_registry_a73640.Get((unsigned int)dialog, record);
    if (record) {
    int kind = record->unknown_6c;
    if (kind == 0x10d || kind == 0xd9 || kind == 0xf0 || kind == 0xce || kind == 0x120 ||
        kind == 0x121 || kind == 0x115 || kind == 0xd3 || kind == 0xcf || kind == 0x11f ||
        kind == 0xc3 || kind == 0x11b || kind == 0xe1 || kind == 0x11e || kind == 0xc4 ||
        kind == 300 || kind == 0xd0 || kind == 0xfc || kind == 0x126) {
        record->unknown_b0 = 2;
        char name[128];
        unsigned int handle = (unsigned int)window;
        GetClassNameA(window, name, sizeof(name));
        if (strcmp(name, "Edit") == 0 || strcmp(name, "NewEdit") == 0) {
            return 0xc0;
        }
        bool wants;
        UnknownControlRecord *control;
        if (strcmp(name, "ListBox") == 0 && unknown_registry_a73640.Get(handle, control)) {
            wants = control->unknown_68 == 1;
        } else if (strcmp(name, "ComboBox") == 0) {
            wants = (GetWindowLongA((HWND)handle, GWL_STYLE) & 3) != 3;
        } else {
            wants = false;
        }
        if (wants) {
            return 0xc0;
        }
    }
    }
    return 0;
}

}
