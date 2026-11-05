// @ref __imp__GetDlgCtrlID@4=0079a3f4
// @ref ?unknown_name_7e8d3c@@3PBDB=007e8d3c
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

void const *__fastcall Unknown_Load_Shape_00495270(char const *filename, bool &allocated);
extern char const *unknown_name_7e8d3c;
extern void *unknown_art_ac1120;
extern void *unknown_art_ac1040;
extern void *unknown_art_ac10fc;
extern void *unknown_art_ac1108;

namespace OwnerDraw {

void const *__fastcall unknown_5e1a80(unsigned int key, HWND window, bool &allocated)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (Is_Listed_Kind_5e8590(kind) && id == 0x71c) {
        return Unknown_Load_Shape_00495270(unknown_name_7e8d3c, allocated);
    }
    if (kind == 0x94) {
        if (id == 0x6ea) {
            return unknown_art_ac1120;
        }
        if (id == 0x6eb) {
            return unknown_art_ac1040;
        }
        if (id == 0x6ec) {
            return unknown_art_ac10fc;
        }
    } else if ((kind == 0x103 || kind == 0xbc7) && id == 0x72b) {
        return unknown_art_ac1108;
    }
    return 0;
}

}
