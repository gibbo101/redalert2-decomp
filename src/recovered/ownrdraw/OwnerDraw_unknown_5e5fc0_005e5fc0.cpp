// @ref ?Unknown_00672F10@UnknownSessionState@@QAEEXZ=00672f10
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_5e4780@OwnerDraw@@YGHPAUHWND__@@J@Z=005e4780
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e5fc0(HWND dialog)
{
    if (unknown_session_a3d298.Unknown_00672F10()) {
        return false;
    }
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)dialog);
    if (!record) {
        return false;
    }
    bool active = record->unknown_bd && record->unknown_b0 == 1;
    bool visible = IsWindowVisible(dialog) != 0;
    if (!active || !visible) {
        return false;
    }
    Voc_Play(Rules->GUIMoveOutSound, 1.0f, 0x2000, 0);
    bool enabled = IsWindowEnabled(dialog) != 0;
    EnableWindow(dialog, FALSE);
    EnumChildWindows(dialog, unknown_5e4780, 1);
    record = unknown_registry_a73640.Find((unsigned int)dialog);
    if (!record) {
        return false;
    }
    record->unknown_be = true;
    InvalidateRect(dialog, 0, FALSE);
    DWORD start = GetTickCount();
    while (!unknown_6000d0()) {
        int done = !record->unknown_be;
        if ((int)(GetTickCount() - start) > 5000 || done) {
            break;
        }
    }
    EnumChildWindows(dialog, unknown_5e4780, 0);
    EnableWindow(dialog, enabled);
    return true;
}

}
