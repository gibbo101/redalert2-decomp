// void Pause_Game_0065c3d0() (0x0065C3D0)
// Pauses the game: aborts a drag select, hides the mouse unless it is
// already hidden, marks the scenario paused and clears the keyboard.
// @ref ?unknown_ab9174@@3HA=00ab9174
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"
#include "shared/unknown_globals.hpp"

void Pause_Game_0065c3d0()
{
    Map.unknown_slot35();
    if (WWMouse->Get_Mouse_State() == 0) {
        WWMouse->Hide_Mouse();
    }
    unknown_id_source_a3d290->unknown_2306 = true;
    unknown_flag_a40d44 = true;
    WWKeyboard->Clear();
    unknown_ab9174 = 0;
}
