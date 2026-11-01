// void BinkClass::Unknown_00430BB0() (0x00430BB0)
// Pauses the movie when the application loses the focus and resumes it (and
// redraws the current frame) when it gets it back. No callers.
#include "shared/movie.hpp"
// @ref ??_C@_0BC@FLCF@Pause?5bink?5movie?6?$AA@=007cf4fc
// @ref ??_C@_0BD@CJNA@Resume?5bink?5movie?6?$AA@=007cf4e8
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28

extern bool unknown_flag_a40d28;                // 0x00A40D28 application active (focus)

void BinkClass::Unknown_00430BB0()
{
    if (!unknown_flag_a40d28) {
        if (unknown_2c == true) {
            Debug_Printf("Pause bink movie\n");
            unknown_2c = false;
            BinkPause(Handle, 1);
        }
    } else if (!unknown_2c) {
        Debug_Printf("Resume bink movie\n");
        unknown_2c = true;
        BinkPause(Handle, 0);
        Unknown_00430820();
    }
}
