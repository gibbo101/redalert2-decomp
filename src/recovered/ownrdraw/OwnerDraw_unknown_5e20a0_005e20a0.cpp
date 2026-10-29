#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

int __fastcall unknown_5e20a0(HWND control)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)control);
    if (record) {
        return record->unknown_c0;
    }
    return -1;
}

}
