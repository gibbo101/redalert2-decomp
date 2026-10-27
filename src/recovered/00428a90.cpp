// 0x00428a90: function not yet identified
//
// Body: 37 bytes (frozen inventory bound).
// Referenced from 23 sites (unconditional call).
// Ghidra prototype: int __fastcall FUN_00428a90(short *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00428a90 {

extern "C" int DAT_008325d0;

int __fastcall FUN_00428a90(short *param_1)
{
    return ((*param_1 - DAT_008325d0) + -1 + (int)param_1[1]) * DAT_008325d0 +
                  (((int)*param_1 - (int)param_1[1]) + -1 + DAT_008325d0 >> 1);
}

}  // namespace seed_00428a90
