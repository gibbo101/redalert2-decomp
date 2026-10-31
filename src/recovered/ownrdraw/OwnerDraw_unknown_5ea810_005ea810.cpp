#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5ea810(HWND control)
{
    UnknownControlRecord *record = unknown_control_record(control);
    if (!record) {
        return false;
    }
    return record->unknown_d8 = record->unknown_6c == 0x108 || record->unknown_6c == 0xbc6;
}

}
