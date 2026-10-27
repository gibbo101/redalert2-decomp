// 0x0052b650: function not yet identified
//
// Body: 52 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void FUN_0052b650(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_0052b650 {

extern "C" undefined4 DAT_00a40cd4;
extern "C" int DAT_00a40ce0;

void  FUN_0052b650(void)
{
    int iVar1;
    int iVar2;

    iVar2 = (int)(0);
    if (0 < DAT_00a40ce0) {
        do {
            for (iVar1 = *(int *)(DAT_00a40cd4 + iVar2 * 4); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x28c))
            {
                *(undefined4 *)(iVar1 + 0x2d8) = 0;
            }
            iVar2 = (int)(iVar2 + 1);
        } while (iVar2 < DAT_00a40ce0);
    }
    return;
}

}  // namespace seed_0052b650
