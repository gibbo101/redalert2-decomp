#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5ea390(HWND control)
{
    UnknownControlRecord *record = unknown_control_record(control);
    if (!record) {
        return false;
    }
    return record->unknown_d6 = record->unknown_6c == 0xbc || record->unknown_6c == 0xbd || record->unknown_6c == 0x102 || record->unknown_6c == 0xc2 || record->unknown_6c == 0xc9;
}

}
