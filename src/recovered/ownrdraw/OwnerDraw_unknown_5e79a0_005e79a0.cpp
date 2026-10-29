// @ref __imp__GetDlgCtrlID@4=0079a3f4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e79a0(unsigned int key, HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (kind == 0x10d) {
        return id == 0x5c1 || id == 0x5c0;
    }
    if (kind == 0xd9) {
        return id == 0x5c1 || id == 0x6ca;
    }
    if (kind == 0xa3) {
        return id == 0x4cf || id == 0x4d0;
    }
    if (kind == 0x105) {
        return id == 0x620 || id == 0x621;
    }
    if (kind == 0xf0) {
        return id == 0x5c0;
    }
    if (kind == 0xce) {
        return id == 0x5ae;
    }
    if (kind == 0x120) {
        return id == 0x5ae || id == 2;
    }
    if (kind == 0x121) {
        return id == 0x5ae || id == 0x5af || id == 2;
    }
    if (kind == 0xea) {
        return id == 0x640 || id == 0x642 || id == 0x641 || id == 0x643 || id == 0x644 || id == 0x645 || id == 0x646 || id == 0x647;
    }
    if (kind == 0xb8) {
        return id == 0x531 || id == 0x535;
    }
    if (kind == 0x11f) {
        return id == 0x5c0;
    }
    if (kind == 0x115) {
        return id == 0x702 || id == 0x686;
    }
    if (kind == 0xd3) {
        return id == 2;
    }
    if (kind == 0xcf) {
        return id == 0x5c2 || id == 2;
    }
    if (kind == 0xc3) {
        return id == 1 || id == 2;
    }
    if (kind == 0x11b) {
        return id == 0x5c2 || id == 0x686;
    }
    if (kind == 0xe1) {
        return id == 1 || id == 2;
    }
    if (kind == 0x11e) {
        return id == 0x5c2 || id == 0x686;
    }
    if (kind == 0xc4) {
        return id == 0x58d || id == 0x58e;
    }
    if (kind == 0xd0) {
        return id == 1;
    }
    if (kind == 0xfc) {
        return id == 1 || id == 2;
    }
    if (kind == 0x126) {
        return id == 6 || id == 7;
    }
    return false;
}

}
