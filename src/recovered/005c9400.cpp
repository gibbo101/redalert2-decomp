// 0x005c9400: function not yet identified
//
// Body: 62 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: int FUN_005c9400(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c9400 {

extern "C" undefined4 DAT_00a3fa98;
extern "C" undefined4 DAT_00a72d34;
extern "C" undefined4 DAT_00a72d38;
extern "C" undefined4 DAT_00a72d3c;

int  FUN_005c9400(void)
{
    int iVar1;
    int iVar2;
    int *piVar3;

    iVar2 = (int)(0);
    piVar3 = (int *)(&DAT_00a3fa98);
    do {
        iVar1 = (int)(*piVar3);
        if ((iVar1 != 0) &&
              (((iVar1 == DAT_00a72d34 || (iVar1 == DAT_00a72d38)) || (iVar1 == DAT_00a72d3c)))) {
            iVar2 = (int)(iVar2 + 1);
        }
        piVar3 = (int *)(piVar3 + 1);
    } while ((int)piVar3 < 0xa3fab8);
    return iVar2;
}

}  // namespace seed_005c9400
