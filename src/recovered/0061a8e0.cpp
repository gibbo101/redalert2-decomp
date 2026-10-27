// 0x0061a8e0: function not yet identified
//
// Body: 58 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __thiscall FUN_0061a8e0(int *param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0061a8e0 {

struct Owner_0061a8e0 { undefined4 FUN_0061a8e0(int *param_2); };

undefined4 Owner_0061a8e0::FUN_0061a8e0(int *param_2)
{
    int * param_1 = (int *)this;
    if ((*param_2 >= *param_1) && (*param_2 < param_1[2] + *param_1)) {
        if ((param_2[1] >= param_1[1]) && (param_2[1] < param_1[3] + param_1[1])) {
            return 1;
        }
    }
    return 0;
}

}  // namespace seed_0061a8e0
