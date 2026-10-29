// @ref __imp__GetDlgCtrlID@4=0079a3f4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e1050(unsigned int key, HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (((((((((kind == 0x94) || (kind == 0xd8)) || (kind == 0xf5)) ||
                    (((kind == 0xe2 || (kind == 0xd5)) ||
                     ((kind == 0x101 || ((kind == 0x129 || (kind == 0xd7)))))))) || (kind == 0xbb)) ||
                ((((kind == 0x100 || (kind == 0xd6)) || (kind == 0x125)) ||
                 (((kind == 0x122 || (kind == 0x112)) ||
                    ((kind == 0xe7 || ((kind == 0x116 || (kind == 0x11d)))))))))) ||
             ((kind == 0x11c ||
                (((((kind == 0xfe || (kind == 0x10f)) || (kind == 0x117)) ||
                    ((kind == 0x114 || (kind == 0xe6)))) ||
                 ((kind == 0xf3 || ((kind == 0xf4 || (kind == 700)))))))))) ||
            ((kind == 0x10e || ((kind == 0xbc6 || (kind == 0xbc7)))))) && (id == 0x71c)) {
        return true;
    }
    if (kind == 0x94) {
        if (((id == 0x6ea) || (id == 0x6ec)) || (id == 0x6eb)) {
            return true;
        }
    }
    else if (kind == 0x103) {
        if (id == 0x72b) {
            return true;
        }
    }
    else if ((kind == 0xbc7) && (id == 0x72b)) {
        return true;
    }
    return false;
}

}
