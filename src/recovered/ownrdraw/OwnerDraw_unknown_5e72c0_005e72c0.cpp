// @ref __imp__GetDlgCtrlID@4=0079a3f4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e72c0(unsigned int key, HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (kind == 0xe2) {
        return id == 0x3ee;
    }
    if (((kind == 0x73) || (kind == 0x10c)) || (kind == 0x103)) {
        return id == 0x423;
    }
    if (kind == 0x108) {
        return id == 0x6d1;
    }
    if ((((kind != 0x94) && (kind != 0xb6)) &&
            ((kind != 0xa3 && ((kind != 0xd8 && (kind != 0xbbb)))))) &&
         ((((kind != 0xf5 &&
                ((((kind != 0xd5 && (kind != 0x2b5)) && (kind != 0xb7)) &&
                 ((kind != 0x2b4 && (kind != 0x101)))))) &&
             ((((kind != 0x129 && ((kind != 0xb5 && (kind != 0xbba)))) && (kind != 0x100)) &&
                (((((kind != 0xb8 && (kind != 0xd6)) && (kind != 0x125)) &&
                    ((kind != 0x116 && (kind != 0x11d)))) && (kind != 0x11c)))))) &&
            (((kind != 0x113 && (kind != 0x109)) &&
             ((kind != 0x10f && ((kind != 0x114 && (kind != 0x10e)))))))))) {
        if ((kind == 0x102) ||
             ((((kind == 0x105 || (kind == 0x6b)) || (kind == 0xbb)) ||
                ((kind == 0x117 || (kind == 0xbc6)))))) {
            return id == 0x5c0;
        }
        if (((((kind == 0xbc) || (kind == 0xbd)) ||
                 ((kind == 0xea || (((kind == 0xd7 || (kind == 0xc2)) || (kind == 0xc9)))))) ||
                ((kind == 700 || (kind == 0xe7)))) ||
             ((kind == 0xe6 ||
                (((kind == 0xf3 || (kind == 0xf4)) ||
                 ((kind == 0x122 || (((kind == 0x112 || (kind == 0xfe)) || (kind == 0xfc)))))))))) {
            return id == 2;
        }
        if (kind == 0xd4) {
            return id == 1;
        }
        if (kind == 0xfb) {
            return id == 7;
        }
        if (kind == 0xff) {
            return id == 0x675;
        }
        return false;
    }
    return id == 0x686;
}

}
