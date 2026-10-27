// 0x004d4730: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_004d4730(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004d4730 {

extern "C" undefined4 DAT_00a35f30;
extern "C" undefined4 DAT_00a35f34;
extern "C" undefined4 DAT_00a35f38;
extern "C" undefined4 DAT_00a35f3c;

void  FUN_004d4730(void)
{
    undefined1 *puVar1;
    int iVar2;

    puVar1 = (undefined1 *)(&DAT_00a35f3c);
    iVar2 = (int)(0x100);
    do {
        *puVar1 = 0;
        puVar1 = (undefined1 *)(puVar1 + 0x6f);
        iVar2 = (int)(iVar2 + -1);
    } while (iVar2 != 0);
    DAT_00a35f30 = 0;
    DAT_00a35f34 = 0;
    DAT_00a35f38 = 0;
    return;
}

}  // namespace seed_004d4730
