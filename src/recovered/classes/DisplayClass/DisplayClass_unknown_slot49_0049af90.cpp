// void DisplayClass::unknown_slot49(int unknown) (0x0049AF90, slot 49)
// Cancels whatever the right mouse button cancels (hypothesis: Westwood's
// Mouse_Right_Press), first match only: a techno waiting for placement, then
// the modes at +0x11AC, +0x11AD, +0x11AE, the target at +0x11B4, the
// waypoint mode +0x11AF and the mode +0x11B0; with none of them, 0x00482BC0.
// Each case restores the default mouse shape.
#include "shared/display.hpp"
// @ref ?Unknown_00482BC0@@YAXXZ=00482bc0
// @ref ?unknown_flag_83740c@@3_NA=0083740c
// @ref ?Unknown_00498F10@DisplayClass@@QAEXH@Z=00498f10

void Unknown_00482BC0();

void DisplayClass::unknown_slot49(int unknown)
{
    UnknownPendingObjectView *pending = unknown_11a0;
    bool techno;
    if (pending != 0) {
        techno = (pending->unknown_14 & 1) != 0;
    }
    if (pending != 0 && techno) {
        unknown_11a0 = 0;
        unknown_11a4 = 0;
        unknown_11a8 = -1;
        Unknown_00498F10(0);
        Set_Default_Mouse(0, unknown_flag_83740c);
        return;
    }
    if (unknown_11ac) {
        Unknown_0049CA20(0);
        Set_Default_Mouse(0, unknown_flag_83740c);
        return;
    }
    if (unknown_11ad) {
        Unknown_0049C7C0(0);
        Set_Default_Mouse(0, unknown_flag_83740c);
        return;
    }
    if (unknown_11ae) {
        Unknown_0049C980(0);
        Set_Default_Mouse(0, unknown_flag_83740c);
        return;
    }
    if (unknown_11b4 != -1) {
        unknown_11b4 = -1;
        Set_Default_Mouse(0, unknown_flag_83740c);
        return;
    }
    if (unknown_11af) {
        Unknown_0049C860(0, false);
        Set_Default_Mouse(0, unknown_flag_83740c);
        return;
    }
    if (unknown_11b0) {
        Unknown_0049CAC0(0);
        Set_Default_Mouse(0, unknown_flag_83740c);
        return;
    }
    Unknown_00482BC0();
    Set_Default_Mouse(0, unknown_flag_83740c);
}
