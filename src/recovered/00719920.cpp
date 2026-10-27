// 0x00719920: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __fastcall FUN_00719920(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00719920 {

int __fastcall FUN_00719920(int param_1)
{
    return *(int *)(param_1 + 4) * 0xc + *(int *)(param_1 + 8) * 0xa4 + 0x1c + *(int *)(param_1 + 0xc)
    ;
}

}  // namespace seed_00719920
