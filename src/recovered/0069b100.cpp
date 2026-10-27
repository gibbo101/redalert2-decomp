// 0x0069b100: function not yet identified
//
// Body: 31 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_0069b100(int param_1,undefined1 param_2,undefined1 param_3,uint param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0069b100 {

struct Owner_0069b100 { void FUN_0069b100(undefined1 param_2, undefined1 param_3, uint param_4); };

void Owner_0069b100::FUN_0069b100(undefined1 param_2, undefined1 param_3, uint param_4)
{
    int param_1 = (int)this;
    *(uint *)(param_1 + 8) = (uint)CONCAT11(param_2,param_3) << 8 | param_4 & 0xff;
    return;
}

}  // namespace seed_0069b100
