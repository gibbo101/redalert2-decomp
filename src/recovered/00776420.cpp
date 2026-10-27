// 0x00776420: function not yet identified
//
// Body: 84 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_00776420(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00776420 {

void __fastcall FUN_00776420(int param_1)
{
    if ((*(byte *)(param_1 + 0x7bc) & 0x40) != 0) {
        (**(code **)(param_1 + 0x58))(param_1,7,0,0);
        *(uint *)(param_1 + 0x7bc) = *(uint *)(param_1 + 0x7bc) & 0xffffffbf;
    }
    (**(code **)(param_1 + 0x58))(param_1,3,0,0);
    if ((*(uint *)(param_1 + 0x7bc) & 0x80000000) == 1) {
        *(uint *)(param_1 + 0x7bc) = *(uint *)(param_1 + 0x7bc) & 0x7fffffff;
    }
    return;
}

}  // namespace seed_00776420
