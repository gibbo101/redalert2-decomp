// 0x006d42f0: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 FUN_006d42f0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006d42f0 {

undefined4 __stdcall FUN_006d42f0(int param_1)
{
    if (((param_1 != 5) && (param_1 != 6)) && (param_1 != 8)) {
        return 1;
    }
    return 0;
}

}  // namespace seed_006d42f0
