#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5ea720(HWND control)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)control);
    if (!record) {
        return false;
    }
    int kind = record->unknown_6c;
    return record->unknown_d7 = kind == 0x103 || kind == 0xbc7;
}

}
