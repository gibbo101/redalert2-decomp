#include "shared/score.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/ms_engine.hpp"
#include "shared/win32_api.hpp"
void ScoreClass::ScoreDelay(int ticks)
{
    CDTimerClass<SystemTimerClass> timer(1);
    do {
        Update_Anims();
        Blit_Score();
        do {
            Service_Game_IO_00481fb0();
            unknown_5b5ee0();
            if(!unknown_flag_a40d28) {
                timer.Stop();
                Wait_While_Inactive();
                timer.Start();
            }
            Sleep(0);
        } while(timer>0);
        timer=1;
        --ticks;
    } while(ticks>0);
}

// External references checked against complete original body operands.
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Update_Anims@ScoreClass@@QAEXXZ=00667620
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_5b5ee0@@YAXXZ=005b5ee0
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref __imp__ClientToScreen@8=0079a4ac
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__Sleep@4=0079a1e4
