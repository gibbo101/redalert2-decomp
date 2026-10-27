// 0x004052f0: function not yet identified
//
// Body: 9 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_004052f0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004052f0 {

void __fastcall FUN_004052f0(int param_1)
{
    *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 8;
    return;
}

}  // namespace seed_004052f0
