// @ref __imp__InvalidateRect@12=0079a494
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

void __fastcall unknown_5e1f30(HWND control, Surface *image)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)control);
    if (record) {
        record->unknown_70 = 2;
        record->image_14 = image;
        InvalidateRect(control, 0, TRUE);
    }
}

}
