// 0x0066e2d0: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 12 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_0066e2d0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0066e2d0 {

struct Owner_0066e2d0 { void FUN_0066e2d0(int param_2); };

void Owner_0066e2d0::FUN_0066e2d0(int param_2)
{
    int param_1 = (int)this;
    if (param_2 == -2) {
        *(undefined4 *)(param_1 + 0x4b) = 0;
        *(undefined4 *)(param_1 + 0x4f) = 0xfffffffe;
        return;
    }
    *(int *)(param_1 + 0x4b) = param_2;
    *(undefined4 *)(param_1 + 0x4f) = 0xffffffff;
    return;
}

}  // namespace seed_0066e2d0
