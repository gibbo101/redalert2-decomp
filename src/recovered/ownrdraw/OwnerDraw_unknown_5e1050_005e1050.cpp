// @ref __imp__GetDlgCtrlID@4=0079a3f4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e1050(unsigned int key, HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (Is_Listed_Kind_5e8590(kind) && id == 0x71c) {
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
