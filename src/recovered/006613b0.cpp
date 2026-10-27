// 0x006613b0: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __thiscall FUN_006613b0(int param_1,int param_2,undefined1 *param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_006613b0 {

struct Owner_006613b0 { bool FUN_006613b0(int param_2, undefined1 *param_3); };

bool Owner_006613b0::FUN_006613b0(int param_2, undefined1 *param_3)
{
    int param_1 = (int)this;
    if ((param_2 >= 0) && (param_2 < 0x32)) {
        *param_3 = *(undefined1 *)(param_1 + param_2 * 0x29 + 0x1238);
        return 1;
    }
    return 0;
}

}  // namespace seed_006613b0
