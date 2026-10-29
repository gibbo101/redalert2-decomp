// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_mouse_release_depth_a76410@OwnerDraw@@3HA=00a76410
#include "shared/mouse.hpp"
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Counts one release off and captures the mouse again once none is left (0x005FF5D0).
int unknown_5ff5d0()
{
    if (unknown_mouse_release_depth_a76410 > 0) {
        --unknown_mouse_release_depth_a76410;
    }
    if (unknown_mouse_release_depth_a76410 == 0 && WWMouse && !WWMouse->Is_Captured()) {
        WWMouse->Capture_Mouse();
    }
    return unknown_mouse_release_depth_a76410;
}

}
