// 0x0078fcc0: function not yet identified
//
// Body: 33 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: int FUN_0078fcc0(char *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078fcc0 {

int  FUN_0078fcc0(char *param_1)
{
    char cVar1;
    int iVar2;

    iVar2 = (int)(0);
    while( true ) {
        cVar1 = (char)(*param_1);
        param_1 = (char *)(param_1 + 1);
        if (((cVar1 < 'A') || ('Z' < cVar1)) && ((cVar1 < 'a' || ('z' < cVar1)))) break;
        iVar2 = (int)(iVar2 + 1);
    }
    return iVar2;
}

}  // namespace seed_0078fcc0
