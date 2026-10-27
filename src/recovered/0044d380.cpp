// 0x0044d380: function not yet identified
//
// Body: 76 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_0044d380(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0044d380 {

void __fastcall FUN_0044d380(int param_1)
{
    int iVar1;
    int iVar2;
    int *piVar3;

    *(undefined1 *)(param_1 + 0x530) = 1;
    iVar2 = (int)(0);
    piVar3 = (int *)(param_1 + 0x454);
    do {
        if ((*(char *)(*(int *)(param_1 + 0x418) + 0xd14 + iVar2) != '\0') &&
              (iVar1 = *piVar3, iVar1 != 0)) {
            *(undefined1 *)(iVar1 + 0x102) = 0;
            *(undefined1 *)(iVar1 + 0x103) = 1;
            *(undefined1 *)(iVar1 + 0x101) = 0;
        }
        iVar2 = (int)(iVar2 + 0x44);
        piVar3 = (int *)(piVar3 + 1);
    } while (iVar2 < 0x4c8);
    return;
}

}  // namespace seed_0044d380
