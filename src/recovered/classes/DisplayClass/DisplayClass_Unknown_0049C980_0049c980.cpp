// void DisplayClass::Unknown_0049C980(int control) (0x0049C980)
// Switches the mode at +0x11AE (-1 toggles, 0 off, 1 on) unless +0x11A4
// is set: resets the mouse and the other modes, then enters the mode when
// the player's +0x230 is positive (0x00482BC0), else leaves it and
// restores the mouse shape.
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_00482BC0@@YAXXZ=00482bc0

void Unknown_00482BC0();

void DisplayClass::Unknown_0049C980(int control)
{
    bool mode = unknown_11ae;
    switch (control) {
    case -1:
        mode = !unknown_11ae;
        break;
    case 0:
        mode = false;
        break;
    case 1:
        mode = true;
        break;
    }
    if (mode != unknown_11ae && !unknown_11a4) {
        Set_Default_Mouse(0, false);
        unknown_11ac = false;
        unknown_11ad = false;
        unknown_11af = false;
        unknown_11b0 = false;
        if (mode && unknown_player_a35db4->unknown_230 > 0) {
            unknown_11ae = true;
            Unknown_00482BC0();
        } else {
            unknown_11ae = false;
            Revert_Mouse_Shape();
        }
    }
}
