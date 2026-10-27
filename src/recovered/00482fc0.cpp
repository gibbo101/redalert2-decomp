// 0x00482fc0: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: char * __fastcall FUN_00482fc0(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00482fc0 {

extern "C" void* PTR_s_Underground_007d38c8;
extern "C" char s__none__007cdecc[];

char * __fastcall FUN_00482fc0(uint param_1)
{
    if (param_1 < 5) {
        return (char *)((&PTR_s_Underground_007d38c8)[param_1]);
    }
    return s__none__007cdecc;
}

}  // namespace seed_00482fc0
