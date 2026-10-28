// void __fastcall Focus_Loss_0065c040() (0x0065C040)
// The game window lost the focus: pauses the sound and keeps the global
// volume (full volume meanwhile), stops the elapsed time in campaign and
// skirmish games, pauses the radar movie, turns tooltips off, aborts a drag
// select, drops a mouse override and redraws the screen with the mouse
// hidden (Westwood's Focus_Loss).
// @ref ?Audio_Pause_All@@YAXXZ=00406e40
// @ref ?Get_Target@AudioLevel@@QAIHXZ=004071e0
// @ref ?unknown_saved_volume_7f1dec@@3HA=007f1dec
// @ref ?Pause_Radar_Movie_005a0a90@@YIX_N@Z=005a0a90
// @ref ??_C@_0BL@KGAC@Paused?5ElapsedTimer?5?$DN?5?$CFld?6?$AA@=007f1e9c
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/audio.hpp"
#include "shared/debug_printf.hpp"
#include "shared/gscreen.hpp"
#include "shared/tool_tip.hpp"
#include "shared/map_view.hpp"
#include "shared/mouse.hpp"

void __fastcall Focus_Loss_0065c040()
{
    Audio_Pause_All();
    unknown_saved_volume_7f1dec = Audio_Global_Levels[7]->Volume.Get_Target();
    Audio_Global_Levels[7]->Volume.Set(0x4000);
    if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5) {
        Debug_Printf("Paused ElapsedTimer = %ld\n", unknown_id_source_a3d290->ElapsedTime.Time());
        unknown_id_source_a3d290->ElapsedTime.Stop();
    }
    Pause_Radar_Movie_005a0a90(true);
    if (ToolTips) {
        ToolTips->Enable(false);
    }
    Map.unknown_slot35();
    Map.Override_Mouse_Shape(0, false);
    WWMouse->Hide_Mouse();
    Map.Flag_To_Redraw(2);
    Map.Render();
    WWMouse->Show_Mouse();
}
