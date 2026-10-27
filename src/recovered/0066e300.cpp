// 0x0066e300: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 8 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_0066e300(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0066e300 {

struct Owner_0066e300 { void FUN_0066e300(int param_2); };

void Owner_0066e300::FUN_0066e300(int param_2)
{
    int param_1 = (int)this;
    if (param_2 == -2) {
        *(undefined4 *)(param_1 + 0x53) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x57) = 0xfffffffe;
        return;
    }
    *(int *)(param_1 + 0x53) = param_2;
    *(undefined4 *)(param_1 + 0x57) = 0xffffffff;
    return;
}

}  // namespace seed_0066e300
