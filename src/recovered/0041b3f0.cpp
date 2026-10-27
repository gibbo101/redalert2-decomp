// 0x0041b3f0: function not yet identified
//
// Body: 15 bytes (frozen inventory bound).
// Referenced from 5 sites (data).
// Ghidra prototype: undefined1 __fastcall FUN_0041b3f0(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0041b3f0 {

undefined1 __fastcall FUN_0041b3f0(int *param_1)
{
    int iVar1;

    iVar1 = (int)((**(code **)(*param_1 + 0x80))());
    return *(undefined1 *)(iVar1 + 0xaab);
}

}  // namespace seed_0041b3f0
