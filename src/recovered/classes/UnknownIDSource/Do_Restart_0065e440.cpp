// void __fastcall Do_Restart_0065e440() (0x0065E440)
// @ref ?unknown_flag_a40380@@3_NA=00a40380
// @ref ?Unknown_005A09E0@@YAXXZ=005a09e0
// @ref ?Unknown_00714410@@YAXXZ=00714410
// @ref ?Unknown_007160D0@@YIXXZ=007160d0
// @ref ?Start_Scenario_0065bc70@@YI_NPBD_NH@Z=0065bc70
// @ref ?Restore_004B5B40@ScenarioCheckpoint_004B5A70@@QAEXXZ=004b5b40
// Restarts the current scenario (name hypothesis from Westwood's Do_Restart;
// reached only through a function pointer): disables the tool tips, stops the
// elapsed game time, closes the sidebar, stops the music, sounds and speech,
// restarts the scenario of the same name and campaign without a briefing,
// restores the checkpointed scenario state, waits out the rest of one second
// and redraws the screen.
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/scenario_checkpoint.hpp"
#include "shared/system_timer.hpp"
#include "shared/cd_timer.hpp"
#include "shared/tool_tip.hpp"
#include "shared/gscreen.hpp"
#include "shared/theme.hpp"
#include "shared/audio.hpp"
#include "shared/vox_class.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_view.hpp"

void __fastcall Do_Restart_0065e440()
{
    unknown_flag_a40d04 = false;
    unknown_flag_a40380 = false;
    if (ToolTips != 0) {
        ToolTips->Enable(false);
    }
    unknown_id_source_a3d290->ElapsedTime.Stop();
    Unknown_005A09E0();
    CDTimerClass<SystemTimerClass> timer;
    timer = 60;
    Theme.Stop(true);
    Audio_Stop();
    Unknown_00714410();
    Speech_Stop(true);
    Unknown_007160D0();
    Map.Set_Default_Mouse(0, false);
    WWKeyboard->Clear();
    Start_Scenario_0065bc70(unknown_id_source_a3d290->FileName, false, unknown_id_source_a3d290->unknown_224c);
    unknown_scenario_checkpoint_00855a90.Restore_004B5B40();
    while (timer.Value() > 0) {
        Service_Game_IO_00481fb0();
    }
    WWKeyboard->Clear();
    if (ToolTips != 0) {
        ToolTips->Enable(unknown_tooltips_enabled_a40b34);
    }
    Map.Render();
}
