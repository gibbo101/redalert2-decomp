// 0x00468ec0: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: char * __fastcall FUN_00468ec0(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00468ec0 {

extern "C" void* PTR_s_Soldier_007d17e4;
extern "C" char s__none__007cdecc[];

char * __fastcall FUN_00468ec0(uint param_1)
{
    if (param_1 < 0xb) {
        return (char *)((&PTR_s_Soldier_007d17e4)[param_1 * 2]);
    }
    return s__none__007cdecc;
}

}  // namespace seed_00468ec0
