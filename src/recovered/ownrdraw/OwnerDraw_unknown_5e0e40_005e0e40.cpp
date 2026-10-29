// @ref __imp__GetDlgCtrlID@4=0079a3f4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e0e40(unsigned int key, HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (((((((kind != 0xbc) && (kind != 0xbd)) && (kind != 0xc2)) && (kind != 0xc9)) ||
             ((((id != 0x6d2 && (id != 0x6d3)) &&
                 ((id != 0x6d4 && ((id != 0x6d5 && (id != 0x6d6)))))) &&
                ((id != 0x6d7 && ((id != 0x6d8 && (id != 0x6d9)))))))) &&
            ((((kind != 0x102 && (((kind != 0xbc && (kind != 0xbd)) && (kind != 0xc2)))) &&
                (kind != 0xc9)) ||
             (((((id != 0x6da && (id != 0x6db)) &&
                    ((id != 0x6dc && ((id != 0x6dd && (id != 0x6de)))))) && (id != 0x6df)) &&
                ((id != 0x6e0 && (id != 0x6e1)))))))) &&
         (((kind != 0xc2 && (kind != 0xc9)) ||
            (((((id != 0x754 && (id != 0x755)) && (id != 0x756)) &&
                (((id != 0x757 && (id != 0x758)) && (id != 0x759)))) &&
             ((id != 0x75a && (id != 0x75b)))))))) {
        return false;
    }
    return true;
}

}
