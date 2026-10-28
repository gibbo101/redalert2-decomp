// void Focus_Restore_0065c140() (0x0065C140)
// The game window regained the focus: restores the mouse shape, restarts
// the elapsed time, restores the tooltips and the global volume, resumes the
// radar movie and the sound (Westwood's Focus_Restore).
// @ref ?Audio_Resume_All@@YAXXZ=00406e70
// @ref ?unknown_saved_volume_7f1dec@@3HA=007f1dec
// @ref ?unknown_tooltips_enabled_a40b34@@3_NA=00a40b34
// @ref ?Pause_Radar_Movie_005a0a90@@YIX_N@Z=005a0a90
// @ref ??_C@_0BL@MEKC@Resume?5ElapsedTimer?5?$DN?5?$CFld?6?$AA@=007f1eb8
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/audio.hpp"
#include "shared/debug_printf.hpp"
#include "shared/gscreen.hpp"
#include "shared/tool_tip.hpp"
#include "shared/map_view.hpp"

void Focus_Restore_0065c140()
{
    Map.Revert_Mouse_Shape();
    unknown_id_source_a3d290->ElapsedTime.Start();
    Debug_Printf("Resume ElapsedTimer = %ld\n", unknown_id_source_a3d290->ElapsedTime.Time());
    if (ToolTips) {
        ToolTips->Enable(unknown_tooltips_enabled_a40b34);
    }
    Audio_Global_Levels[7]->Volume.Set(unknown_saved_volume_7f1dec);
    unknown_saved_volume_7f1dec = 0x4000;
    Pause_Radar_Movie_005a0a90(false);
    Audio_Resume_All();
}
