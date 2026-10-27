// 0x007114f0: function not yet identified
//
// Body: 191 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void FUN_007114f0(void)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007114f0 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00ad074c;
extern "C" undefined4 DAT_00ad0758;
extern "C" undefined4 DAT_00ad07a0;

void  FUN_007114f0(void)
{
    int iVar1;
    int *piVar2;
    int iVar3;
    int iVar4;

    iVar3 = (int)(DAT_00ad0758);
    while (iVar3 = iVar3 + -1, iVar3 >= 0) {
        iVar1 = (int)(*(int *)(DAT_00ad074c + iVar3 * 4));
        piVar2 = (int *)(*(int **)(iVar1 + 0x9c));
        if (piVar2 != (int *)0x0) {
            iVar4 = (int)(0);
            if (*piVar2 >= 0) {
                do {
                    iVar4 = (int)(iVar4 + 1);
                    *(undefined4 *)(piVar2[2] + -4 + iVar4 * 4) = 0;
                } while (iVar4 <= *piVar2);
            }
            *piVar2 = 0;
            iVar4 = (int)(*(int *)(iVar1 + 0x9c));
            if (iVar4 != 0) {
                FUN_00781d3b((undefined4)(*(undefined4 *)(iVar4 + 8)));
                FUN_00781d3b((undefined4)(iVar4));
            }
            *(undefined4 *)(iVar1 + 0x9c) = 0;
        }
        if (*(int *)(iVar1 + 0xa0) != 0) {
            FUN_00781d3b((undefined4)(*(int *)(iVar1 + 0xa0)));
            *(undefined4 *)(iVar1 + 0xa0) = 0;
        }
        if (*(int *)(iVar1 + 0xb0) != 0) {
            FUN_00781d3b((undefined4)(*(int *)(iVar1 + 0xb0)));
            *(undefined4 *)(iVar1 + 0xb0) = 0;
        }
        *(undefined4 *)(iVar1 + 0x98) = 0;
    }
    if (DAT_00ad07a0 != 0) {
        FUN_00781d3b((undefined4)(DAT_00ad07a0));
        DAT_00ad07a0 = 0;
    }
    return;
}

}  // namespace seed_007114f0
