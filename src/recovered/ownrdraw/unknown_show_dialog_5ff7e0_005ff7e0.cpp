// @ref ?unknown_replace_edit_5ecb00@OwnerDraw@@YGHPAUHWND__@@J@Z=005ecb00
// @ref ?unknown_5ed180@OwnerDraw@@YGHPAUHWND__@@J@Z=005ed180
// @ref ?unknown_5e8720@OwnerDraw@@YGHPAUHWND__@@J@Z=005e8720
// @ref ?unknown_5e7eb0@OwnerDraw@@YGHPAUHWND__@@J@Z=005e7eb0
// @ref ?unknown_5e8130@OwnerDraw@@YGHPAUHWND__@@J@Z=005e8130
// @ref ?unknown_set_control_art_5ea960@OwnerDraw@@YIXI@Z=005ea960
// @ref ?unknown_5e9fa0@OwnerDraw@@YI_NPAUHWND__@@@Z=005e9fa0
// @ref ?unknown_dialog_a763cc@OwnerDraw@@3PAUHWND__@@A=00a763cc
// @ref ?unknown_735ba0@@YIXPAUHWND__@@@Z=00735ba0
// @ref ?unknown_737060@@YIXPAUHWND__@@@Z=00737060
// @ref ?unknown_dialog_5ecf40@@YGXPAUHWND__@@H@Z=005ecf40
// @ref ?unknown_5eac30@OwnerDraw@@YIXXZ=005eac30
// @ref ?unknown_session_a3d298@@3VUnknownSessionState@@A=00a3d298
// @ref ?Unknown_00672F10@UnknownSessionState@@QAEEXZ=00672f10
// @ref ?unknown_screen_widths_7add68@@3PAHA=007add68
// @ref ?unknown_screen_heights_7add74@@3PAHA=007add74
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?Get@UnknownControlIndex@OwnerDraw@@QBE_NABIAAPAUUnknownControlRecord@2@@Z=00601710
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/session_state.hpp"
#include "shared/campaign_score.hpp"
#include "shared/main_opt.hpp"
#include "shared/rect.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/lobby.hpp"

void __fastcall unknown_735ba0(HWND window);
void __fastcall unknown_737060(HWND window);

namespace OwnerDraw {

// EnumChildWindows callbacks and the dialog test 0x005FF7E0 runs over a dialog (not yet recovered).
BOOL __stdcall unknown_5ed180(HWND window, LPARAM lparam);
BOOL __stdcall unknown_5e8720(HWND window, LPARAM lparam);
BOOL __stdcall unknown_5e7eb0(HWND window, LPARAM lparam);
BOOL __stdcall unknown_5e8130(HWND window, LPARAM lparam);
bool __fastcall unknown_5e9fa0(HWND dialog);

// Prepares a dialog's controls for owner drawing: art by the control kind, the listed setters, the movie
// frame size, and the per-control callbacks.
inline void unknown_prepare_dialog(HWND dialog, int kind)
{
    unknown_735ba0(dialog);
    unknown_5eaaa0(dialog, kind);
    if (!unknown_session_a3d298.Unknown_00672F10()) {
        unknown_set_control_art_5ea960((unsigned int)dialog);
    }
    unknown_5ea550(dialog);
    unknown_5ea390(dialog);
    unknown_5ea720(dialog);
    unknown_5ea810(dialog);
    EnumChildWindows(dialog, unknown_5e8720, 0);
    if (unknown_5e9fa0(dialog)) {
        Point2D size;
        size.X = unknown_screen_widths_7add68[0];
        size.Y = unknown_screen_heights_7add74[0];
        Unknown_005E9F00(dialog, &size);
    } else {
        unknown_5ea230(dialog);
    }
    EnumChildWindows(dialog, unknown_5e7eb0, 0);
    EnumChildWindows(dialog, unknown_5e8130, 0);
    unknown_737060(dialog);
}

}

// Subclasses a dialog's controls for owner drawing and prepares them (0x005FF7E0).
void __fastcall unknown_show_dialog_5ff7e0(void *handle, int kind)
{
    using namespace OwnerDraw;
    HWND dialog = (HWND)handle;
    unknown_5eac30();
    unknown_dialog_a763cc = dialog;
    EnumChildWindows(dialog, (WNDENUMPROC)unknown_dialog_5ecf40, 1);
    unknown_dialog_5ecf40(dialog, 1);
    EnumChildWindows(dialog, unknown_replace_edit_5ecb00, 1);
    EnumChildWindows(dialog, unknown_5ed180, 0);
    unknown_5ed180(dialog, 0);
    EnumChildWindows(dialog, (WNDENUMPROC)unknown_dialog_5ecf40, 0);
    unknown_dialog_5ecf40(dialog, 0);
    unknown_prepare_dialog(dialog, kind);
}
