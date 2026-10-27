// 0x00468ea0: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: char * __fastcall FUN_00468ea0(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00468ea0 {

extern "C" void* PTR_s_Soldier_007d17e0;
extern "C" char s__none__007cdecc[];

char * __fastcall FUN_00468ea0(uint param_1)
{
    if (param_1 < 0xb) {
        return (char *)((&PTR_s_Soldier_007d17e0)[param_1 * 2]);
    }
    return s__none__007cdecc;
}

}  // namespace seed_00468ea0
