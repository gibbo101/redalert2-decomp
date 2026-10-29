// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?unknown_5e5150@OwnerDraw@@YIXPAUHWND__@@_N@Z=005e5150
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/campaign_score.hpp"

// When the dialog's record has its +0xBE flag set: notifies control 0x71A (0x4E2), calls 0x005E5150
// and clears the flag (0x005E5F20).
void __fastcall unknown_dialog_5e5f20(HWND window)
{
    OwnerDraw::UnknownControlRecord *record = OwnerDraw::unknown_registry_a73640.Find((unsigned int)window);
    if (record && record->unknown_be) {
        HWND item = GetDlgItem(window, 0x71a);
        if (item) {
            SendMessageA(item, 0x4e2, 0, 0);
        }
        OwnerDraw::unknown_5e5150(window, false);
        record->unknown_be = false;
    }
}
