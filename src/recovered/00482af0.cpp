// 0x00482af0: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined * __fastcall FUN_00482af0(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00482af0 {

extern "C" undefined4 DAT_007ce9b4;
extern "C" void* PTR_s_North_0079ab50;

undefined * __fastcall FUN_00482af0(uint param_1)
{
    if (param_1 < 5) {
        return (unsigned char *)((&PTR_s_North_0079ab50)[param_1]);
    }
    return (unsigned char *)(&DAT_007ce9b4);
}

}  // namespace seed_00482af0
