#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

void __fastcall unknown_5e6330(HWND control)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)control);
    if (record) {
        record->unknown_bd = false;
    }
}

}
