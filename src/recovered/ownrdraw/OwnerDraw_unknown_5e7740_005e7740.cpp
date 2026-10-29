// @ref ?Unknown_00672F10@UnknownSessionState@@QAEEXZ=00672f10
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e7740(unsigned int key, HWND window)
{
    if (unknown_session_a3d298.Unknown_00672F10()) {
        return false;
    }
    if (unknown_5e7230(key, window)) {
        return true;
    }
    if (unknown_5e7620(key, window)) {
        return true;
    }
    return false;
}

}
