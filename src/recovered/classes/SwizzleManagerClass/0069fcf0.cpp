// 0x0069fcf0: function not yet identified
//
// Owner: SwizzleManagerClass, virtual slot 9 (vtable +0x24) (from RTTI/vtables).
// Body: 27 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 FUN_0069fcf0(undefined4 param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0069fcf0 {

undefined4 __stdcall FUN_0069fcf0(undefined4 param_1, undefined4 *param_2)
{
    if (param_2 == (undefined4 *)0x0) {
        return 0x80004003;
    }
    *param_2 = 4;
    return 0;
}

}  // namespace seed_0069fcf0
