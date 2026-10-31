#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// A control's registry record, or null. The setters 0x005EA390..0x005EAAA0 read their record through it;
// 0x005FF7E0 inlines them with this helper's Get left out of line, which needs the key as its own local.
inline UnknownControlRecord *unknown_control_record(HWND control)
{
    unsigned int key = (unsigned int)control;
    UnknownControlRecord *record = 0;
    unknown_registry_a73640.Get(key, record);
    return record;
}

bool __fastcall unknown_5ea230(HWND control)
{
    UnknownControlRecord *record = 0;
    unknown_registry_a73640.Get(*(unsigned int *)&control, record);
    if (!record) {
        return false;
    }
    int kind = record->unknown_6c;
    bool special = kind == 0x10d ||
        kind == 0xd9 ||
        kind == 0xf0 ||
        kind == 0xce ||
        kind == 0x120 ||
        kind == 0x121 ||
        kind == 0x115 ||
        kind == 0xd3 ||
        kind == 0xcf ||
        kind == 0x11f ||
        kind == 0xc3 ||
        kind == 0x11b ||
        kind == 0xe1 ||
        kind == 0x11e ||
        kind == 0xc4 ||
        kind == 300 ||
        kind == 0xd0 ||
        kind == 0xfc ||
        kind == 0x126;
    if (special) {
        record->unknown_b0 = 2;
    }
    return special;
}

}
