// 0x0078469d: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_0078469d(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078469d {

extern undefined4  FUN_0078969b(void);

void  FUN_0078469d(undefined4 param_1)
{
    int iVar1;

    iVar1 = (int)(FUN_0078969b());
    *(undefined4 *)(iVar1 + 0x14) = param_1;
    return;
}

}  // namespace seed_0078469d
