// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_mouse_release_depth_a76410@OwnerDraw@@3HA=00a76410
#include "shared/mouse.hpp"
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Releases a captured mouse and counts one more release (0x005FF5A0).
int unknown_5ff5a0()
{
    if (WWMouse && WWMouse->Is_Captured() == true) {
        WWMouse->Release_Mouse();
    }
    return ++unknown_mouse_release_depth_a76410;
}

}
