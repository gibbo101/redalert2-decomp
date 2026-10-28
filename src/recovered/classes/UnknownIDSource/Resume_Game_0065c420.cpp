// void Resume_Game_0065c420() (0x0065C420)
// Resumes a paused game: shows the mouse again, clears the paused mark and
// the keyboard.
// @ref ?unknown_ab9174@@3HA=00ab9174
#include "shared/id_source.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"
#include "shared/unknown_globals.hpp"

void Resume_Game_0065c420()
{
    if (unknown_id_source_a3d290->unknown_2306 == true) {
        while (WWMouse->Get_Mouse_State() != 0) {
            WWMouse->Show_Mouse();
        }
    }
    unknown_id_source_a3d290->unknown_2306 = false;
    unknown_flag_a40d44 = false;
    WWKeyboard->Clear();
    unknown_ab9174 = 0;
}
