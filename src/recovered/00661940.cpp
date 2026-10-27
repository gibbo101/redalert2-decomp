// 0x00661940: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __fastcall FUN_00661940(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00661940 {

int __fastcall FUN_00661940(int param_1)
{
    int iVar1;
    char *pcVar2;
    int iVar3;

    iVar1 = (int)(0);
    pcVar2 = (char *)(param_1 + 0x1a12);
    iVar3 = (int)(0x32);
    do {
        if (*pcVar2 != '\0') {
            iVar1 = (int)(iVar1 + 1);
        }
        pcVar2 = (char *)(pcVar2 + 0x29);
        iVar3 = (int)(iVar3 + -1);
    } while (iVar3 != 0);
    return iVar1;
}

}  // namespace seed_00661940
