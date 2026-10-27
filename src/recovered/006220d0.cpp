// 0x006220d0: function not yet identified
//
// Body: 8 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined * __fastcall FUN_006220d0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_006220d0 {

extern "C" void* PTR_DAT_007a8620;

undefined * __fastcall FUN_006220d0(int param_1)
{
    return (unsigned char *)((&PTR_DAT_007a8620)[param_1]);
}

}  // namespace seed_006220d0
