#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

void __fastcall unknown_5eaaa0(HWND control, int value)
{
    UnknownControlRecord *record = unknown_control_record(control);
    if (record) {
        record->unknown_6c = value;
    }
}

}
