// 0x004f6bc0: function not yet identified
//
// Body: 23 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_004f6bc0(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004f6bc0 {

struct Owner_004f6bc0 { void FUN_004f6bc0(undefined1 param_2, undefined1 param_3, undefined1 param_4); };

void Owner_004f6bc0::FUN_004f6bc0(undefined1 param_2, undefined1 param_3, undefined1 param_4)
{
    undefined1 * param_1 = (undefined1 *)this;
    *param_1 = param_2;
    param_1[1] = param_3;
    param_1[2] = param_4;
    return;
}

}  // namespace seed_004f6bc0
