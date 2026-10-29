// @ref __imp__GetDlgCtrlID@4=0079a3f4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace seed_005df660 {
unsigned char __fastcall FUN_005df660(int param_1);   // 0x005DF660
}

namespace OwnerDraw {

bool __fastcall unknown_5e76b0(unsigned int key, HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (seed_005df660::FUN_005df660(kind) && id == 0x695) {
        return true;
    }
    return false;
}

}
