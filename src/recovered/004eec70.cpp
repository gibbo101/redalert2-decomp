// 0x004eec70: function not yet identified
//
// Body: 54 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_004eec70(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004eec70 {

struct Owner_004eec70 { void FUN_004eec70(int param_2); };

void Owner_004eec70::FUN_004eec70(int param_2)
{
    int param_1 = (int)this;
    int iVar1;

    iVar1 = (int)(0);
    if (0 < *(int *)(param_1 + 0x551c)) {
        do {
            if (*(int *)(*(int *)(param_1 + 0x5510) + iVar1 * 8) == param_2) {
                *(undefined1 *)(*(int *)(param_1 + 0x5510) + iVar1 * 8 + 4) = 1;
            }
            iVar1 = (int)(iVar1 + 1);
        } while (iVar1 < *(int *)(param_1 + 0x551c));
    }
    return;
}

}  // namespace seed_004eec70
