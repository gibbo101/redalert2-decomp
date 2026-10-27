// 0x0078298a: function not yet identified
//
// Body: 18 bytes (frozen inventory bound).
// Referenced from 302 sites (unconditional call).
// Ghidra prototype: int FUN_0078298a(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078298a {

extern undefined4  FUN_0078290c(undefined4 param_1);

int  FUN_0078298a(undefined4 param_1)
{
    int iVar1;

    iVar1 = (int)(FUN_0078290c((undefined4)(param_1)));
    return (iVar1 != 0) - 1;
}

}  // namespace seed_0078298a
