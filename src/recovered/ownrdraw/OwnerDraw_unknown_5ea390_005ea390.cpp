#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5ea390(HWND control)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)control);
    if (!record) {
        return false;
    }
    int kind = record->unknown_6c;
    return record->unknown_d6 = kind == 0xbc || kind == 0xbd || kind == 0x102 || kind == 0xc2 || kind == 0xc9;
}

}
