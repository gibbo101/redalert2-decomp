#include "shared/options.hpp"
#include "shared/cd_timer.hpp"
#include "shared/mouse.hpp"
#include "shared/audio.hpp"
#include "shared/tool_tip.hpp"
#include "shared/gscreen.hpp"
#include "shared/vox_class.hpp"
#include "shared/vox_speech.hpp"
#include "shared/session_state.hpp"

// Pauses for a dialog once (+0x3080 records it); see the declaration.
void UnknownSessionState::Unknown_00672DE0()
{
    if (!unknown_3080 && unknown_flag_a40958) {
        unknown_3080 = true;
        if (unknown_game_speed_7f3230 == -1) {
            unknown_game_speed_7f3230 = Options.GameSpeed;
        }
        if (Type == 0) {
            Options.GameSpeed = 2;
        }
        if (!unknown_id_source_a3d290->unknown_2306) {
            Pause_Game_0065c3d0();
            unknown_ab9174 = Frame + 3;
        }
        if (!WWMouse->Is_Captured()) {
            WWMouse->Capture_Mouse();
        }
        Audio_Global_Levels[7]->Volume.Set(0x4000);
    }
}
// @ref ?unknown_game_speed_7f3230@@3HA=007f3230
