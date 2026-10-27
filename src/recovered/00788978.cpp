// 0x00788978: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_00788978(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00788978 {

extern "C" code * DAT_00b2b0c0;

undefined4  FUN_00788978(undefined4 param_1)
{
    int iVar1;

    if ((uint)(DAT_00b2b0c0) != (uint)((code *)0x0)) {
        iVar1 = (int)((*DAT_00b2b0c0)(param_1));
        if (iVar1 != 0) {
            return 1;
        }
    }
    return 0;
}

}  // namespace seed_00788978
