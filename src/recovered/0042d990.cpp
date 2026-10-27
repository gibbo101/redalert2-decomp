// 0x0042d990: function not yet identified
//
// Body: 71 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0042d990(void)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042d990 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_0084e8d0;
extern "C" undefined4 DAT_0084e930;

void  FUN_0042d990(void)
{
    int iVar1;
    int *piVar2;
    int iVar3;

    if (DAT_0084e930 != 0) {
        piVar2 = (int *)(&DAT_0084e8d0);
        iVar1 = (int)(8);
        do {
            iVar3 = (int)(3);
            do {
                if (*piVar2 != 0) {
                    FUN_00781d3b((undefined4)(*piVar2));
                    *piVar2 = 0;
                }
                piVar2 = (int *)(piVar2 + 1);
                iVar3 = (int)(iVar3 + -1);
            } while (iVar3 != 0);
            iVar1 = (int)(iVar1 + -1);
        } while (iVar1 != 0);
        DAT_0084e930 = 0;
    }
    return;
}

}  // namespace seed_0042d990
