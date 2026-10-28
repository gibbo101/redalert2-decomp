// void Release_Pause_0065c310() (0x0065C310)
// Lowers the pause count; the last release resumes the game (unless it was
// paused before the count rose), restarts the elapsed time and resumes the
// sound.
// @ref ?unknown_was_paused_ab6ef4@@3_NA=00ab6ef4
// @ref ?unknown_ab9174@@3HA=00ab9174
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Audio_Resume_All@@YAXXZ=00406e70
#include "shared/id_source.hpp"
#include "shared/audio.hpp"

void Release_Pause_0065c310()
{
    if (unknown_id_source_a3d290->unknown_62c) {
        unknown_id_source_a3d290->unknown_62c--;
        if (unknown_id_source_a3d290->unknown_62c == 0) {
            if (!unknown_was_paused_ab6ef4) {
                Resume_Game_0065c420();
            }
            unknown_id_source_a3d290->ElapsedTime.Start();
            Audio_Resume_All();
        }
    }
}
