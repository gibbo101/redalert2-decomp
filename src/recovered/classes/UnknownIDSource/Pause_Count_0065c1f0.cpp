// void __fastcall Pause_Count_0065c1f0(int seconds) (0x0065C1F0)
// Raises the pause count. A positive seconds (re)starts the +0x620 timer
// (seconds * 60 ticks) and does nothing more when one already ran. The first
// pause pauses the sound, stops the elapsed time in campaign and skirmish
// games and pauses the game unless it already was.
// @ref ?unknown_was_paused_ab6ef4@@3_NA=00ab6ef4
// @ref ?unknown_ab9174@@3HA=00ab9174
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Audio_Pause_All@@YAXXZ=00406e40
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/audio.hpp"

void __fastcall Pause_Count_0065c1f0(int seconds)
{
    if (seconds) {
        unknown_id_source_a3d290->unknown_620 = seconds * 60;
        if (unknown_id_source_a3d290->unknown_630) {
            return;
        }
        unknown_id_source_a3d290->unknown_630 = true;
    }
    if (unknown_id_source_a3d290->unknown_62c == 0) {
        Audio_Pause_All();
        if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5) {
            unknown_id_source_a3d290->ElapsedTime.Stop();
        }
        unknown_was_paused_ab6ef4 = unknown_id_source_a3d290->unknown_2306;
        if (!unknown_was_paused_ab6ef4) {
            Pause_Game_0065c3d0();
        }
    }
    unknown_id_source_a3d290->unknown_62c++;
}
