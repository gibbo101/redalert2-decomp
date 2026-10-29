// void __fastcall Unknown_006F7670() (0x006F7670)
// When the stopwatch of 0x006F7650 is running it is stopped; if it ran at most 500 ms
// (timeGetTime difference, absolute) 0x006F7360 runs and the screen is redrawn completely.
// @ref __imp__timeGetTime@0=0079a524
// @ref ?unknown_flag_ac133d@@3_NA=00ac133d
// @ref ?unknown_time_ac1340@@3KA=00ac1340
// @ref ?Unknown_006F7360@@YIXXZ=006f7360
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Map@@3VMouseClass@@A=008324e0
#include "shared/uicmnds.hpp"
#include "shared/map_view.hpp"

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern bool unknown_flag_ac133d;
extern unsigned long unknown_time_ac1340;
void __fastcall Unknown_006F7360();

void __fastcall Unknown_006F7670()
{
    if (unknown_flag_ac133d) {
        unknown_flag_ac133d = false;
        if (abs((int)(timeGetTime() - unknown_time_ac1340)) <= 500) {
            Unknown_006F7360();
            Map.Flag_To_Redraw(1);
        }
    }
}
