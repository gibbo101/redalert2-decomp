// 0x00717af0: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void FUN_00717af0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00717af0 {

extern "C" undefined4 DAT_00ae3408;

void  FUN_00717af0(void)
{
    int iVar1;
    undefined4 *puVar2;

    puVar2 = (undefined4 *)(&DAT_00ae3408);
    for (iVar1 = 0x4000; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = (undefined4 *)(puVar2 + 1);
    }
    return;
}

}  // namespace seed_00717af0
