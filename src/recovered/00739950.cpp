// 0x00739950: function not yet identified
//
// Body: 96 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_00739950(int param_1,int param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00739950 {

struct Owner_00739950 { void FUN_00739950(int param_2, int param_3); };

void Owner_00739950::FUN_00739950(int param_2, int param_3)
{
    int param_1 = (int)this;
    bool bVar1;

    if (param_2 == *(int *)(param_1 + 0x10)) {
        if ((param_3 == 2) && (*(char *)(param_1 + 0x14) == '\0')) {
            *(undefined1 *)(param_1 + 0x14) = 1;
            *(undefined1 *)(param_1 + 8) = 1;
            return;
        }
    }
    else {
        bVar1 = (bool)(param_3 >= *(int *)(param_1 + 0x18));
        if (*(int *)(param_1 + 0x10) == 0) {
            bVar1 = (bool)(true);
        }
        else if (!bVar1) {
            return;
        }
        if ((param_2 != 0) && (bVar1)) {
            if (param_3 == 3) {
                *(undefined1 *)(param_1 + 0x14) = 0;
            }
            *(int *)(param_1 + 0x10) = param_2;
            *(int *)(param_1 + 0x18) = param_3;
            *(undefined1 *)(param_1 + 8) = 1;
        }
    }
    return;
}

}  // namespace seed_00739950
