// 0x006a6860: function not yet identified
//
// Body: 81 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_006a6860(int param_1,int param_2,int *param_3,int *param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006a6860 {

void __fastcall FUN_006a6860(int param_1, int param_2, int *param_3, int *param_4)
{
    *param_3 = ((param_2 * 2 + param_1) * 0xf) / 0x240 + -0x10000;
    *param_4 = ((param_2 * 2 - param_1) * 0xf) / 0x240 + 0x10000;
    return;
}

}  // namespace seed_006a6860
