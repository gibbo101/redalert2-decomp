// 0x0055aa50: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_0055aa50(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0055aa50 {

void __fastcall FUN_0055aa50(int param_1)
{
    *(int *)(param_1 + 0x118) = *(int *)(param_1 + 0xf8) + 1 + *(int *)(param_1 + 0xfc);
    *(int *)(param_1 + 0x11c) =
              (*(int *)(param_1 + 0xf0) - *(int *)(param_1 + 0xf8)) + *(int *)(param_1 + 0xfc);
    return;
}

}  // namespace seed_0055aa50
