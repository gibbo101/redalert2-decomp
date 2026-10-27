// 0x0069be30: function not yet identified
//
// Body: 12 bytes (frozen inventory bound).
// Referenced from 2 sites (computed call, data).
// Ghidra prototype: void __fastcall FUN_0069be30(undefined4 param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0069be30 {

extern undefined4 __fastcall FUN_0069bd60(void);

void __fastcall FUN_0069be30(undefined4 param_1, undefined4 *param_2)
{
    undefined4 uVar1;

    uVar1 = (undefined4)(FUN_0069bd60());
    *param_2 = uVar1;
    return;
}

}  // namespace seed_0069be30
