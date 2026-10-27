// 0x007858af: function not yet identified
//
// Body: 25 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_007858af(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007858af {

extern undefined4  FUN_0078ddac(undefined4 *param_1);
extern undefined4  FUN_0078de9e(int *param_1);

undefined4  FUN_007858af(undefined4 param_1)
{
    int iVar1;
    undefined4 uVar2;

    iVar1 = (int)(FUN_0078de9e((int *)(param_1)));
    if (iVar1 != 0) {
        uVar2 = (undefined4)(FUN_0078ddac((undefined4 *)(iVar1)));
        return uVar2;
    }
    return 0;
}

}  // namespace seed_007858af
