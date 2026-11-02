// void WWMouseClass::Process_Mouse() (0x00773400)
// Mouse thread callback (TibSun WWMouseClass::Process_Mouse): reads the
// Windows cursor (unless 0x00522E80 holds the position), then moves the
// drawn cursor; while the screen surface is unavailable it only records the
// position and marks the next move as forced.
#include "shared/wwmouse.hpp"
// @ref ?unknown_function_522e80@@YAHXZ=00522e80
// @ref ?unknown_flag_b2af68@@3_NA=00b2af68

void WWMouseClass::Process_Mouse()
{
    if (ScreenSurface != 0) {
        Block_Mouse();

        int x;
        int y;
        if (unknown_function_522e80()) {
            x = MouseX;
            y = MouseY;
        } else {
            Get_Cursor_Position(x, y);
            MouseX = x;
            MouseY = y;
        }
        if (!ScreenSurface->Unknown_Slot26() && !unknown_flag_b2af68) {
            DrawX = x;
            DrawY = y;
            unknown_flag_b2af68 = true;
        } else {
            Move_Cursor(x, y, unknown_flag_b2af68);
            unknown_flag_b2af68 = false;
        }

        Unblock_Mouse();
    }
}
