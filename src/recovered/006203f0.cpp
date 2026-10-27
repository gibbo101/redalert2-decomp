// 0x006203f0: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: float10 __thiscall FUN_006203f0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_006203f0 {

struct Owner_006203f0 { float10 FUN_006203f0(int param_2); };

float10 Owner_006203f0::FUN_006203f0(int param_2)
{
    int param_1 = (int)this;
    if (param_2 >= *(char *)(param_1 + 0x61)) {
        return (float10)*(double *)(param_1 + 0x48);
    }
    return (float10)*(double *)(param_1 + 8 + param_2 * 8) / (float10)*(double *)(param_1 + 0x48);
}

}  // namespace seed_006203f0
