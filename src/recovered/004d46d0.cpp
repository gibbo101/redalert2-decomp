// 0x004d46d0: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_004d46d0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004d46d0 {

extern "C" undefined4 DAT_00a32338;
extern "C" undefined4 DAT_00a3233c;
extern "C" undefined4 DAT_00a32340;
extern "C" undefined4 DAT_00a32344;

void  FUN_004d46d0(void)
{
    undefined1 *puVar1;
    int iVar2;

    puVar1 = (undefined1 *)(&DAT_00a32344);
    iVar2 = (int)(0x80);
    do {
        *puVar1 = 0;
        puVar1 = (undefined1 *)(puVar1 + 0x6f);
        iVar2 = (int)(iVar2 + -1);
    } while (iVar2 != 0);
    DAT_00a32338 = 0;
    DAT_00a3233c = 0;
    DAT_00a32340 = 0;
    return;
}

}  // namespace seed_004d46d0
