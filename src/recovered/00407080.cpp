// 0x00407080: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 26 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_00407080(uint *param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00407080 {

void __fastcall FUN_00407080(uint *param_1, int param_2)
{
    *param_1 = *param_1 | 1;
    param_1[2] = param_2 << 0x10;
    return;
}

}  // namespace seed_00407080
