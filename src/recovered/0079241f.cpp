// 0x0079241f: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_0079241f(undefined4 param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0079241f {

extern void  FUN_007845f9(char *param_1);
extern void  FUN_0078464b(char *param_1);
extern undefined4  FUN_00792448(uint param_1, int *param_2);

undefined4  FUN_0079241f(undefined4 param_1, undefined4 param_2)
{
    undefined4 uVar1;

    FUN_007845f9((char *)(param_2));
    uVar1 = (undefined4)(FUN_00792448((uint)(param_1), (int *)(param_2)));
    FUN_0078464b((char *)(param_2));
    return uVar1;
}

}  // namespace seed_0079241f
