// 0x005c8cd0: function not yet identified
//
// Body: 21 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_005c8cd0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_005c8cd0 {

extern "C" undefined4 * DAT_00a3fa80;
extern "C" undefined4 DAT_00a3fa94;
extern "C" undefined4 DAT_00a3fa98;

void __fastcall FUN_005c8cd0(int param_1)
{
    DAT_00a3fa94 = param_1;
    (&DAT_00a3fa98)[param_1] = *DAT_00a3fa80;
    return;
}

}  // namespace seed_005c8cd0
