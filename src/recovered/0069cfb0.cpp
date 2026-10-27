// 0x0069cfb0: function not yet identified
//
// Body: 10 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_0069cfb0(int param_1,undefined1 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0069cfb0 {

struct Owner_0069cfb0 { void FUN_0069cfb0(undefined1 param_2); };

void Owner_0069cfb0::FUN_0069cfb0(undefined1 param_2)
{
    int param_1 = (int)this;
    *(undefined1 *)(param_1 + 0x57) = param_2;
    return;
}

}  // namespace seed_0069cfb0
