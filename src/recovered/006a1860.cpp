// 0x006a1860: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_006a1860(int param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006a1860 {

extern "C" undefined4 DAT_008323cc;

void __fastcall FUN_006a1860(int param_1, undefined4 param_2, undefined4 param_3)
{
    *(undefined4 *)(param_1 + 0x24) = param_2;
    *(undefined4 *)(param_1 + 0x50) = DAT_008323cc;
    *(undefined4 *)(param_1 + 0x20) = param_3;
    *(undefined1 *)(param_1 + 0x2d) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
    return;
}

}  // namespace seed_006a1860
