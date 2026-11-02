// void __stdcall OwnerDraw::Unknown_00601050(unsigned int key, HWND window) (0x00601050): marks the control's
// registry record (+0xD4, as SimpleDialogControl::Set_Window 0x006010F0 does) and nothing else. No reference to
// it survives in the executable; the stdcall two-argument ABI (ret 8, no this) is a hypothesis.
#include "shared/owner_draw_dialog_control.hpp"
// @ref ?unknown_registry_a73640@OwnerDraw@@=00a73640

namespace OwnerDraw {

void __stdcall Unknown_00601050(unsigned int key, HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    if (record) record->unknown_d4 = true;
}

}
