// @ref __imp__GetDlgCtrlID@4=0079a3f4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/rules.hpp"

namespace OwnerDraw {

int __fastcall unknown_5e06c0(unsigned int key, HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (((kind == 0x103) || (kind == 0xbc7)) && (id == 0x6f4)) {
        return Rules->MessageCharTyped;
    }
    return -1;
}

}
