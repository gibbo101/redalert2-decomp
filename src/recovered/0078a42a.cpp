// 0x0078a42a: function not yet identified
//
// Body: 36 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_0078a42a(int *param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078a42a {

extern undefined4  FUN_00782be1(int param_1);
extern undefined4  FUN_0078a3f9(undefined4 *param_1);

undefined4  FUN_0078a42a(int *param_1, undefined4 param_2)
{
    undefined4 uVar1;
    int iVar2;

    do {
        *param_1 = *param_1 + 1;
        uVar1 = (undefined4)(FUN_0078a3f9((undefined4 *)(param_2)));
        iVar2 = (int)(FUN_00782be1((int)(uVar1)));
    } while (iVar2 != 0);
    return uVar1;
}

}  // namespace seed_0078a42a
