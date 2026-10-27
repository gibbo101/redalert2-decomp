// 0x00776480: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_00776480(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00776480 {

void __fastcall FUN_00776480(int param_1)
{
    (**(code **)(param_1 + 0x58))(param_1,4,0,0);
    *(uint *)(param_1 + 0x7bc) = *(uint *)(param_1 + 0x7bc) | 0x40;
    return;
}

}  // namespace seed_00776480
