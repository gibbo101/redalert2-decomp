// void Unknown_006F7650() (0x006F7650)
// Starts a stopwatch: once, flag 0x00AC133D is raised and timeGetTime is stamped at 0x00AC1340.
// @ref __imp__timeGetTime@0=0079a524
// @ref ?unknown_flag_ac133d@@3_NA=00ac133d
// @ref ?unknown_time_ac1340@@3KA=00ac1340

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern bool unknown_flag_ac133d;
extern unsigned long unknown_time_ac1340;

void Unknown_006F7650()
{
    if (!unknown_flag_ac133d) {
        unknown_flag_ac133d = true;
        unknown_time_ac1340 = timeGetTime();
    }
}
