// 0x00406100: function not yet identified
//
// Body: 52 bytes (frozen inventory bound).
// Referenced from 8 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_00406100(int *param_1,int param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00406100 {

extern "C" undefined4 DAT_00830fac;

void __fastcall FUN_00406100(int *param_1, int param_2, int param_3)
{
    if ((undefined4 *)param_1[3] == &DAT_00830fac) {
        *param_1 = param_2;
        param_1[2] = param_3;
        if (param_2 != 0) {
            param_1[1] = *(int *)(param_2 + 0x138);
            if (param_3 == 0) {
                param_1[2] = *(int *)(param_2 + 0x24);
            }
            *(int **)(param_2 + 0x278) = param_1;
        }
    }
    return;
}

}  // namespace seed_00406100
