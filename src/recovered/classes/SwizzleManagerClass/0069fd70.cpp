// 0x0069fd70: function not yet identified
//
// Owner: SwizzleManagerClass, virtual slot 5 (vtable +0x14) (from RTTI/vtables).
// Body: 31 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 FUN_0069fd70(undefined4 param_1,int param_2,int *param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0069fd70 {

undefined4 __stdcall FUN_0069fd70(undefined4 param_1, int param_2, int *param_3)
{
    if ((param_2 != 0) && (param_3 != (int *)0x0)) {
        *param_3 = param_2;
        return 0;
    }
    return 0x80004003;
}

}  // namespace seed_0069fd70
