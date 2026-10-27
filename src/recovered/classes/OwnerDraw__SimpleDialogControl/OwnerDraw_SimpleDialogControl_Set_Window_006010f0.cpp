#include "shared/owner_draw_dialog_control.hpp"
void OwnerDraw::SimpleDialogControl::Set_Window_006010f0(unsigned int key, HWND value)
{
    window = value;
    OwnerDraw::UnknownControlRecord *record = OwnerDraw::unknown_registry_a73640.Find(key);
    if (record) record->unknown_d4 = true;
    unknown_08 = true;
}
// @ref ?unknown_registry_a73640@OwnerDraw@@=00a73640
