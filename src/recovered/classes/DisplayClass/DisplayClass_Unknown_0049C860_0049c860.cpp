// void DisplayClass::Unknown_0049C860(int control, bool keep) (0x0049C860)
// The waypoint-mode switch (+0x11AF; -1 toggles, 0 off, 1 on) unless +0x11A4
// is set: clears the other modes, then enters waypoint mode with a free path
// (or, with keep, the player's current path, +0x154), else leaves it;
// leaving restores the coordinate at +0x11BC to where +0x11B8 points and
// shows the mouse again.
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
#include "shared/mouse.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_004F30D0@HouseClass@@QAEHXZ=004f30d0
// @ref ?Unknown_00482BC0@@YAXXZ=00482bc0
// @ref ?WWMouse@@3PAVMouse@@A=00839c68

void Unknown_00482BC0();

void DisplayClass::Unknown_0049C860(int control, bool keep)
{
    bool mode = unknown_11af;
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
    if (mode != unknown_11af && !unknown_11a4) {
        unknown_11ac = false;
        unknown_11ad = false;
        unknown_11ae = false;
        unknown_11b0 = false;
        int path = unknown_player_a35db4->Unknown_004F30D0();
        if (mode) {
            if (path == -1 && (!keep || unknown_player_a35db4->unknown_154 == -1)) {
                unknown_11af = false;
                Revert_Mouse_Shape();
                unknown_11b8 = 0;
                return;
            }
            unknown_11af = true;
            if (!keep) {
                unknown_player_a35db4->unknown_154 = path;
            }
            Unknown_00482BC0();
            return;
        }
        unknown_11af = false;
        Revert_Mouse_Shape();
        if (unknown_11b8) {
            *unknown_11b8 = *(CoordStruct *)&unknown_11bc;
            unknown_11b8 = 0;
            WWMouse->Show_Mouse();
        }
    }
}
