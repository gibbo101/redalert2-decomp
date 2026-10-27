// 0x004d4700: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_004d4700(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004d4700 {

extern "C" undefined4 DAT_00866270;
extern "C" undefined4 DAT_00866274;
extern "C" undefined4 DAT_00866278;
extern "C" undefined4 DAT_0086627c;

void  FUN_004d4700(void)
{
    undefined1 *puVar1;
    int iVar2;

    puVar1 = (undefined1 *)(&DAT_0086627c);
    iVar2 = (int)(0x4000);
    do {
        *puVar1 = 0;
        puVar1 = (undefined1 *)(puVar1 + 0x6f);
        iVar2 = (int)(iVar2 + -1);
    } while (iVar2 != 0);
    DAT_00866270 = 0;
    DAT_00866274 = 0;
    DAT_00866278 = 0;
    return;
}

}  // namespace seed_004d4700
