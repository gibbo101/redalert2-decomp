// 0x0052b6f0: function not yet identified
//
// Body: 49 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: int __thiscall FUN_0052b6f0(int *param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0052b6f0 {

struct Owner_0052b6f0 { int FUN_0052b6f0(int param_2); };

int Owner_0052b6f0::FUN_0052b6f0(int param_2)
{
    int * param_1 = (int *)this;
    int *piVar1;

    piVar1 = (int *)(**(code **)(*param_1 + 0x9c))();
    if (piVar1 != (int *)0x0) {
        if (piVar1[param_2 % (piVar1[1] * *piVar1) + 4] != 0) {
            return (int)*(char *)(piVar1[param_2 % (piVar1[1] * *piVar1) + 4] + 0x2a);
        }
    }
    return 0;
}

}  // namespace seed_0052b6f0
