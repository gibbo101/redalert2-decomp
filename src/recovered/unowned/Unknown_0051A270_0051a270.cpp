// bool Unknown_0051A270() -- 0x0051A270
// Releases the archive at 0x008374F0 (as CD::Swap_Disk releases its mixfiles).
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_mix_8374f0@@3PAV?$MixFileClass@VCCFileClass@@@@A=008374f0
// @ref ??_C@_0BD@MGDA@?5?5?5?5?5Releasing?5?$CFs?6?$AA@=007d2208

bool __cdecl Unknown_0051A270()
{
    if (unknown_mix_8374f0 != 0) {
        Debug_Printf("     Releasing %s\n", unknown_mix_8374f0->Filename);
        delete unknown_mix_8374f0;
        unknown_mix_8374f0 = 0;
    }
    return true;
}
