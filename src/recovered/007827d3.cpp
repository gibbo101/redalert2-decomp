// 0x007827d3: function not yet identified
//
// Body: 47 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_007827d3(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007827d3 {

extern undefined4  FUN_00782802(char *param_1, uint param_2, uint param_3, int *param_4);
extern void  FUN_007845f9(char *param_1);
extern void  FUN_0078464b(char *param_1);

undefined4  FUN_007827d3(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
    undefined4 uVar1;

    FUN_007845f9((char *)(param_4));
    uVar1 = (undefined4)(FUN_00782802((char *)(param_1), (uint)(param_2), (uint)(param_3), (int *)(param_4)));
    FUN_0078464b((char *)(param_4));
    return uVar1;
}

}  // namespace seed_007827d3
