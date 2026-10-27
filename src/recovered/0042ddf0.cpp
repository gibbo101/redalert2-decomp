// 0x0042ddf0: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_0042ddf0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042ddf0 {

extern undefined4  FUN_00783622(short *param_1, short *param_2, int param_3);

struct Owner_0042ddf0 { void FUN_0042ddf0(int param_2); };

void Owner_0042ddf0::FUN_0042ddf0(int param_2)
{
    int param_1 = (int)this;
    int iVar1;
    undefined4 *puVar2;

    puVar2 = (undefined4 *)(param_1 + 0xe);
    for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = (undefined4 *)(puVar2 + 1);
    }
    if (param_2 != 0) {
        FUN_00783622((short *)((undefined4 *)(param_1 + 0xe)), (short *)(param_2), (int)(0x7f));
    }
    return;
}

}  // namespace seed_0042ddf0
