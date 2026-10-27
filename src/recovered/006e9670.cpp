// 0x006e9670: function not yet identified
//
// Body: 172 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void FUN_006e9670(void)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_006e9670 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00ac0b34;
extern "C" int DAT_00ac0b40;

void  FUN_006e9670(void)
{
    int iVar1;
    int *piVar2;
    int iVar3;
    int iVar4;

    iVar4 = (int)(0);
    if (0 < DAT_00ac0b40) {
        do {
            iVar1 = (int)(*(int *)(DAT_00ac0b34 + iVar4 * 4));
            piVar2 = (int *)(*(int **)(iVar1 + 0xf4));
            if (piVar2 != (int *)0x0) {
                iVar3 = (int)(0);
                if (*piVar2 >= 0) {
                    do {
                        iVar3 = (int)(iVar3 + 1);
                        *(undefined4 *)(piVar2[2] + -4 + iVar3 * 4) = 0;
                    } while (iVar3 <= *piVar2);
                }
                *piVar2 = 0;
                iVar3 = (int)(*(int *)(iVar1 + 0xf4));
                if (iVar3 != 0) {
                    FUN_00781d3b((undefined4)(*(undefined4 *)(iVar3 + 8)));
                    FUN_00781d3b((undefined4)(iVar3));
                }
                *(undefined4 *)(iVar1 + 0xf4) = 0;
            }
            if (*(int *)(iVar1 + 0xfc) != 0) {
                FUN_00781d3b((undefined4)(*(int *)(iVar1 + 0xfc)));
                *(undefined4 *)(iVar1 + 0xfc) = 0;
            }
            if (*(int *)(iVar1 + 0xf8) != 0) {
                FUN_00781d3b((undefined4)(*(int *)(iVar1 + 0xf8)));
                *(undefined4 *)(iVar1 + 0xf8) = 0;
            }
            *(undefined4 *)(iVar1 + 0xf0) = 0;
            iVar4 = (int)(iVar4 + 1);
        } while (iVar4 < DAT_00ac0b40);
    }
    return;
}

}  // namespace seed_006e9670
