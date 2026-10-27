// 0x00713170: function not yet identified
//
// Body: 61 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: undefined4 __thiscall FUN_00713170(int param_1,uint param_2,uint param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00713170 {

struct Owner_00713170 { undefined4 FUN_00713170(uint param_2, uint param_3); };

undefined4 Owner_00713170::FUN_00713170(uint param_2, uint param_3)
{
    int param_1 = (int)this;
    if (param_2 > *(uint *)(param_1 + 0x40)) {
        return 0xffffffff;
    }
    if (param_3 < *(uint *)(param_1 + 0x3c)) {
        return 0;
    }
    if (param_2 > *(uint *)(param_1 + 0x3c)) {
        *(uint *)(param_1 + 0x3c) = param_2;
    }
    if (param_3 < *(uint *)(param_1 + 0x40)) {
        *(uint *)(param_1 + 0x40) = param_3;
    }
    return *(undefined4 *)(param_1 + 0x40);
}

}  // namespace seed_00713170
