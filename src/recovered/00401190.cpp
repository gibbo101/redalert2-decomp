// 0x00401190: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: int __fastcall FUN_00401190(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00401190 {

int __fastcall FUN_00401190(int param_1, int param_2)
{
    return (int)((*(uint *)(param_1 + 0x2c) >> 0x10) * param_2) / 100;
}

}  // namespace seed_00401190
