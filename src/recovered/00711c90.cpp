// 0x00711c90: function not yet identified
//
// Body: 135 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_00711c90(int param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00711c90 {

extern void  FUN_00781d3b(undefined4 param_1);

void __fastcall FUN_00711c90(int param_1)
{
    int *piVar1;
    int iVar2;

    piVar1 = (int *)(*(int **)(param_1 + 0x9c));
    if (piVar1 != (int *)0x0) {
        iVar2 = (int)(0);
        if (*piVar1 >= 0) {
            do {
                iVar2 = (int)(iVar2 + 1);
                *(undefined4 *)(piVar1[2] + -4 + iVar2 * 4) = 0;
            } while (iVar2 <= *piVar1);
        }
        *piVar1 = 0;
        iVar2 = (int)(*(int *)(param_1 + 0x9c));
        if (iVar2 != 0) {
            FUN_00781d3b((undefined4)(*(undefined4 *)(iVar2 + 8)));
            FUN_00781d3b((undefined4)(iVar2));
        }
        *(undefined4 *)(param_1 + 0x9c) = 0;
    }
    if (*(int *)(param_1 + 0xa0) != 0) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 0xa0)));
        *(undefined4 *)(param_1 + 0xa0) = 0;
    }
    if (*(int *)(param_1 + 0xb0) != 0) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 0xb0)));
        *(undefined4 *)(param_1 + 0xb0) = 0;
    }
    *(undefined4 *)(param_1 + 0x98) = 0;
    return;
}

}  // namespace seed_00711c90
