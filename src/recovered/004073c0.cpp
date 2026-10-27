// 0x004073c0: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int * __fastcall FUN_004073c0(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004073c0 {

int * __fastcall FUN_004073c0(int *param_1)
{
    param_1 = (int *)*param_1;
    if ((param_1 == (int *)param_1[2]) && (param_1 = (int *)*param_1, param_1 == (int *)param_1[2])) {
        param_1 = (int *)0x0;
    }
    return param_1;
}

}  // namespace seed_004073c0
