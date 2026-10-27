// 0x007764c0: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_007764c0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007764c0 {

void __fastcall FUN_007764c0(int param_1)
{
    (**(code **)(param_1 + 0x58))(param_1,7,0,0);
    *(uint *)(param_1 + 0x7bc) = *(uint *)(param_1 + 0x7bc) & 0xffffffbf;
    return;
}

}  // namespace seed_007764c0
