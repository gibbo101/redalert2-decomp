// 0x00663220: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_00663220(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00663220 {

extern "C" undefined4 _DAT_00ab6e88;

void __fastcall FUN_00663220(int param_1)
{
    undefined4 *puVar1;
    int iVar2;

    puVar1 = (undefined4 *)(param_1 + 0x632);
    iVar2 = (int)(0x65);
    do {
        *puVar1 = _DAT_00ab6e88;
        puVar1 = (undefined4 *)(puVar1 + 1);
        iVar2 = (int)(iVar2 + -1);
    } while (iVar2 != 0);
    return;
}

}  // namespace seed_00663220
