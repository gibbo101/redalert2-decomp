// bool Unknown_0051A2B0() -- 0x0051A2B0
// Releases the archive at 0x008374F0 and opens NEUTRAL.MIX in its place.
// Body 0x0051A2B0-0x0051A32B (124 bytes; the inventory's 59 stops at the
// operator new call).
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_mix_8374f0@@3PAV?$MixFileClass@VCCFileClass@@@@A=008374f0
// @ref ??_C@_0BD@MGDA@?5?5?5?5?5Releasing?5?$CFs?6?$AA@=007d2208
// @ref ??0?$MixFileClass@VCCFileClass@@@@QAE@PBDPBVPKey@@@Z=005952f0
// @ref ?FastKey@@3VPKey@@A=00839010
// @ref ?Unknown_00496460@@YAXPBD@Z=00496460
// @ref ??_C@_0BD@PMEL@LOADED?5NEUTRAL?4MIX?$AA@=007dd8f4
// @ref ??_C@_0M@HJIF@NEUTRAL?4MIX?$AA@=007dd908

// Shows a loading message (0x00496460; hypothesis).
void __cdecl Unknown_00496460(char const *text);

bool __cdecl Unknown_0051A2B0()
{
    if (unknown_mix_8374f0 != 0) {
        Debug_Printf("     Releasing %s\n", unknown_mix_8374f0->Filename);
        delete unknown_mix_8374f0;
        unknown_mix_8374f0 = 0;
    }
    unknown_mix_8374f0 = new MixFileClass<CCFileClass>("NEUTRAL.MIX", &FastKey);
    if (unknown_mix_8374f0 == 0) {
        return false;
    }
    Unknown_00496460("LOADED NEUTRAL.MIX");
    return true;
}
