// 0x0078dbb0: function not yet identified
//
// Body: 42 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 FUN_0078dbb0(int param_1,undefined4 param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078dbb0 {

extern void  FUN_0078db54(uint param_1, char *param_2, uint param_3, int param_4);

undefined4  FUN_0078dbb0(int param_1, undefined4 param_2, int param_3)
{
    undefined4 uVar1;

    uVar1 = (undefined4)(0);
    if ((param_3 == 10) && (param_1 < 0)) {
        uVar1 = (undefined4)(1);
    }
    FUN_0078db54((uint)(param_1), (char *)(param_2), (uint)(param_3), (int)(uVar1));
    return param_2;
}

}  // namespace seed_0078dbb0
