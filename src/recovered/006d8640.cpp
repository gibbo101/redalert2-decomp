// 0x006d8640: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_006d8640(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006d8640 {

undefined4 __stdcall FUN_006d8640(int *param_1)
{
    if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
        return 1;
    }
    return 0;
}

}  // namespace seed_006d8640
