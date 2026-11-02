// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?Blit_Rects@MSEngine@@QAEXPAVSurface@@@Z=005b33a0
// @ref ?Check_Focus@MSEngine@@QAEXXZ=005b3670
// @ref ?Draw@MSEngine@@QAEXPAVSurface@@@Z=005b2fb0
// @ref ?unknown_481fb0@@YAXXZ=00481fb0
// @ref ?unknown_4961d0@@YAXXZ=004961d0
// @ref ?unknown_5b5ee0@@YAXXZ=005b5ee0
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref __imp__Sleep@4=0079a1e4
// Advance the animation engine for the requested number of ticks (005B3550).
#include "shared/ms_engine.hpp"
#include "shared/ms_anim.hpp"
void MSEngine::Run(int frames)
{
    CDTimerClass<SystemTimerClass> timer(1);
    do {
        do {
            unknown_481fb0();
            Unknown_Slot2();
            unknown_4961d0();
            Draw(unknown_surface_839954);
            Blit_Rects(unknown_surface_839954);
            unknown_5b5ee0();
            if (!unknown_flag_a40d28) {
                timer.Stop();
                Check_Focus();
                timer.Start();
            }
            Sleep(0);
        } while (timer.Value()>0);
        timer=1;
        --frames;
    } while (frames!=0);
}
