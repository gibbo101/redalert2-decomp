// 0x00783a14: function not yet identified
//
// Body: 49 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_00783a14(undefined4 param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00783a14 {

extern void  FUN_0078464b(char *param_1);
extern undefined4  FUN_0078aec6(undefined4 param_1, char *param_2, undefined4 param_3, undefined4 *param_4);
extern undefined4  FUN_0078b036(void);

undefined4  FUN_00783a14(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    int iVar1;
    undefined4 uVar2;

    iVar1 = (int)(FUN_0078b036());
    if (iVar1 == 0) {
        return 0;
    }
    uVar2 = (undefined4)(FUN_0078aec6((undefined4)(param_1), (char *)(param_2), (undefined4)(param_3), (undefined4 *)(iVar1)));
    FUN_0078464b((char *)(iVar1));
    return uVar2;
}

}  // namespace seed_00783a14
