#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

int __fastcall unknown_5ea900(HWND control)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)control);
    if (record) {
        return record->unknown_e4;
    }
    return 0;
}

}
