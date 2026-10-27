// 0x00784502: function not yet identified
//
// Body: 59 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_00784502(undefined4 param_1,undefined4 param_2,undefined4 param_3)
// Callees with accepted source:
//   FUN_0078ae9c -> src/recovered/0078ae9c.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784502 {

extern void  FUN_007845f9(char *param_1);
extern void  FUN_0078464b(char *param_1);
extern undefined4  FUN_00786535(undefined4 param_1, byte *param_2, undefined4 *param_3);
extern undefined4  FUN_0078ae0f(undefined4 *param_1);
extern void  FUN_0078ae9c(int param_1, undefined4 *param_2);

undefined4  FUN_00784502(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    undefined4 uVar1;
    undefined4 uVar2;

    FUN_007845f9((char *)(param_1));
    uVar1 = (undefined4)(FUN_0078ae0f((undefined4 *)(param_1)));
    uVar2 = (undefined4)(FUN_00786535((undefined4)(param_1), (byte *)(param_2), (undefined4 *)(param_3)));
    FUN_0078ae9c((int)(uVar1), (undefined4 *)(param_1));
    FUN_0078464b((char *)(param_1));
    return uVar2;
}

}  // namespace seed_00784502
