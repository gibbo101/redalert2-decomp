// 0x004b9430: function not yet identified
//
// Body: 8 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined1 __fastcall FUN_004b9430(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004b9430 {

undefined1 __fastcall FUN_004b9430(int param_1)
{
    undefined1 uVar1;

    uVar1 = (undefined1)(*(undefined1 *)(param_1 + 0x59));
    *(undefined1 *)(param_1 + 0x59) = 0;
    return uVar1;
}

}  // namespace seed_004b9430
