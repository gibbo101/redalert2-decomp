// 0x0072a770: function not yet identified
//
// Body: 59 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: undefined4 __thiscall FUN_0072a770(int param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0072a770 {

struct Owner_0072a770 { undefined4 FUN_0072a770(int *param_2); };

undefined4 Owner_0072a770::FUN_0072a770(int *param_2)
{
    int param_1 = (int)this;
    if ((*param_2 >= *(int *)(param_1 + 0x54)) &&
          (*param_2 < *(int *)(param_1 + 0x5c) + *(int *)(param_1 + 0x54))) {
        if ((param_2[1] >= *(int *)(param_1 + 0x58)) &&
              (param_2[1] < *(int *)(param_1 + 0x60) + *(int *)(param_1 + 0x58))) {
            return 1;
        }
    }
    return 0;
}

}  // namespace seed_0072a770
