// void DisplayClass::Unknown_0049CA20(int control) (0x0049CA20; hypothesis: Repair_Mode_Control)
// Switches the mode at +0x11AC (-1 toggles, 0 off, 1 on) unless +0x11A4
// is set: clears the other modes, resets the mouse, then enters the mode
// when the player's +0x230 is positive (0x00482BC0), else leaves it and
// restores the mouse shape.
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_00482BC0@@YAXXZ=00482bc0

void Unknown_00482BC0();

void DisplayClass::Unknown_0049CA20(int control)
{
    bool mode = unknown_11ac;
    switch (control) {
    case -1:
        mode = !unknown_11ac;
        break;
    case 0:
        mode = false;
        break;
    case 1:
        mode = true;
        break;
    }
    if (mode != unknown_11ac && !unknown_11a4) {
        unknown_11ad = false;
        unknown_11ae = false;
        unknown_11af = false;
        unknown_11b0 = false;
        Set_Default_Mouse(0, false);
        if (mode && unknown_player_a35db4->unknown_230 > 0) {
            unknown_11ac = true;
            Unknown_00482BC0();
        } else {
            unknown_11ac = false;
            Revert_Mouse_Shape();
        }
    }
}
