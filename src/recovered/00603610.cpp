// 0x00603610: function not yet identified
//
// Body: 40 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __fastcall FUN_00603610(char *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00603610 {

int __fastcall FUN_00603610(char *param_1)
{
    char cVar1;
    int iVar2;

    iVar2 = (int)(0);
    cVar1 = (char)(*param_1);
    while (cVar1 != '\0') {
        iVar2 = (int)(((int)cVar1 + iVar2 * 0x1a) % 0x1f);
        param_1 = (char *)(param_1 + 1);
        cVar1 = (char)(*param_1);
    }
    return iVar2;
}

}  // namespace seed_00603610
