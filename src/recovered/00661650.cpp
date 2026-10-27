// 0x00661650: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __thiscall FUN_00661650(int param_1,int param_2,undefined1 *param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00661650 {

struct Owner_00661650 { bool FUN_00661650(int param_2, undefined1 *param_3); };

bool Owner_00661650::FUN_00661650(int param_2, undefined1 *param_3)
{
    int param_1 = (int)this;
    if ((param_2 >= 0) && (param_2 < 0x32)) {
        *param_3 = *(undefined1 *)(param_1 + param_2 * 0x29 + 0x1a3a);
        return 1;
    }
    return 0;
}

}  // namespace seed_00661650
