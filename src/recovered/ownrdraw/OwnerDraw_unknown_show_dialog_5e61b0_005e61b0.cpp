// @ref ?Unknown_00672F10@UnknownSessionState@@QAEEXZ=00672f10
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_5e5150@OwnerDraw@@YIXPAUHWND__@@_N@Z=005e5150
// @ref ?unknown_5e4780@OwnerDraw@@YGHPAUHWND__@@J@Z=005e4780
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"

namespace OwnerDraw {

bool __fastcall unknown_show_dialog_5e61b0(HWND dialog)
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
    Voc_Play(Rules->GUIMoveInSound, 1.0f, 0x2000, 0);
    bool enabled = IsWindowEnabled(dialog) != 0;
    EnableWindow(dialog, FALSE);
    EnumChildWindows(dialog, unknown_5e4780, 1);
    unknown_5e5150(dialog, true);
    EnumChildWindows(dialog, unknown_5e4780, 0);
    EnableWindow(dialog, enabled);
    InvalidateRect(dialog, 0, FALSE);
    return true;
}

}
