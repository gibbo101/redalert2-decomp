// 0x00784e11: function not yet identified
//
// Body: 33 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_00784e11(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784e11 {

extern undefined4  FUN_00784e32(uchar *param_1);
extern void  FUN_00785c86(int param_1);
extern void  FUN_00785ce7(int param_1);

undefined4  FUN_00784e11(undefined4 param_1)
{
    undefined4 uVar1;

    FUN_00785c86((int)(0xc));
    uVar1 = (undefined4)(FUN_00784e32((uchar *)(param_1)));
    FUN_00785ce7((int)(0xc));
    return uVar1;
}

}  // namespace seed_00784e11
