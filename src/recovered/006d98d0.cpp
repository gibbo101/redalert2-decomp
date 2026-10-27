// 0x006d98d0: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 3 sites (data).
// Ghidra prototype: int FUN_006d98d0(int *param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_006d98d0 {

int  FUN_006d98d0(int *param_1, int *param_2)
{
    if (*param_1 == *param_2) {
        return 0;
    }
    return ((*param_1 >= *param_2) - 1 & 0xfffffffe) + 1;
}

}  // namespace seed_006d98d0
