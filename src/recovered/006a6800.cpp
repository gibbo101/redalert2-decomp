// 0x006a6800: function not yet identified
//
// Body: 90 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_006a6800(int param_1,int param_2,int *param_3,int *param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006a6800 {

void __fastcall FUN_006a6800(int param_1, int param_2, int *param_3, int *param_4)
{
    *param_3 = (param_1 * 0x3c) / 2;
    *param_4 = (param_1 * 0x1e) / 2;
    *param_3 = *param_3 + (param_2 * -0x3c) / 2;
    *param_4 = *param_4 + (param_2 * 0x1e) / 2;
    return;
}

}  // namespace seed_006a6800
