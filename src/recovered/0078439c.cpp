// 0x0078439c: function not yet identified
//
// Body: 47 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_0078439c(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078439c {

extern undefined4  FUN_007843cb(int param_1);
extern undefined4  FUN_0078445e(int param_1);
extern void  FUN_007845f9(char *param_1);
extern void  FUN_0078464b(char *param_1);

undefined4  FUN_0078439c(int param_1)
{
    undefined4 uVar1;

    if (param_1 == 0) {
        uVar1 = (undefined4)(FUN_0078445e((int)(0)));
        return uVar1;
    }
    FUN_007845f9((char *)(param_1));
    uVar1 = (undefined4)(FUN_007843cb((int)(param_1)));
    FUN_0078464b((char *)(param_1));
    return uVar1;
}

}  // namespace seed_0078439c
