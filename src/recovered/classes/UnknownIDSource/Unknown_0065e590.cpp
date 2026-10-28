// void __fastcall Unknown_0065e590() (0x0065E590)
// Ends the scenario on "battle control terminated" (reached only through a
// function pointer; Westwood's Do_Abort-like ending, name not recovered):
// stops the elapsed game time, sets +0x834 to 1, closes the sidebar, clears
// the keyboard, erases the mouse, stops the music, fades the global volume
// out, says EVA_BattleControlTerminated and waits for it (at most 300 ticks),
// stops the speech and sounds, restores the volume and switches back to
// 640 x 480 when the display mode was toggled.
// @ref ??_C@_0BM@CEIN@EVA_BattleControlTerminated?$AA@=007f20d4
// @ref ?Audio_Wait_Drain@@YIXPAUAudioLevel@@@Z=00406fe0
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/system_timer.hpp"
#include "shared/t_timer.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/gscreen.hpp"
#include "shared/theme.hpp"
#include "shared/audio.hpp"
#include "shared/vox_class.hpp"
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"
#include "shared/map_view.hpp"
#include "shared/dsurface.hpp"

void __fastcall Unknown_0065e590()
{
    unknown_flag_a40d04 = false;
    unknown_flag_a40380 = false;
    unknown_id_source_a3d290->ElapsedTime.Stop();
    unknown_id_source_a3d290->TechLevel = 1;
    Unknown_005A09E0();
    WWKeyboard->Clear();
    WWMouse->Erase_Mouse(unknown_surface_839954, false);
    WWMouse->Release_Mouse();
    Map.Set_Default_Mouse(0, false);
    Theme.Stop(true);
    Audio_Level_Fade_To_Zero(&Audio_Global_Levels[7]->Volume);
    Unknown_00715B40("EVA_BattleControlTerminated", 2, -1);
    Audio_Wait_Drain(&Audio_Global_Levels[7]->Volume);
    long end = TickCount.Time() + 300;
    while (Speech_Is_Playing() && end > TickCount.Time()) {
        Service_Game_IO_00481fb0();
    }
    Speech_Stop(true);
    Unknown_007160D0();
    Audio_Stop();
    Unknown_00714410();
    Audio_Global_Levels[7]->Volume.Set(0x4000);
    Toggle_Display_Mode_0065c480(false);
    unknown_flag_a40958 = false;
}
