// void DisplayClass::Unknown_0049CAC0(int control) (0x0049CAC0)
// The mode switch for +0x11B0 (-1 toggles, 0 off, 1 on) unless +0x11A4 is
// set. The requested state starts from +0x11AC (as written in the
// original); turning on also needs 0x0042E700 to allow the player's house.
// Clears the other modes and resets the mouse, then enters the mode
// (0x00482BC0) or leaves it and restores the mouse shape.
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_object_84e8d0@@3VUnknown84E8D0@@A=0084e8d0
// @ref ?Unknown_0042E700@Unknown84E8D0@@QAE_NH@Z=0042e700
// @ref ?Unknown_00482BC0@@YAXXZ=00482bc0

void Unknown_00482BC0();

void DisplayClass::Unknown_0049CAC0(int control)
{
    bool mode = unknown_11ac;
    switch (control) {
    case -1:
        mode = !mode;
        break;
    case 0:
        mode = false;
        break;
    case 1:
        mode = true;
        break;
    }
    if (mode != unknown_11b0 && !unknown_11a4) {
        if (mode && !unknown_object_84e8d0.Unknown_0042E700(unknown_player_a35db4->ArrayIndex)) {
            mode = false;
        }
        unknown_11ad = false;
        unknown_11ae = false;
        unknown_11af = false;
        unknown_11ac = false;
        Set_Default_Mouse(0, false);
        if (mode) {
            unknown_11b0 = true;
            Unknown_00482BC0();
        } else {
            unknown_11b0 = false;
            Revert_Mouse_Shape();
        }
    }
}
