// 0x0073bdb0: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_0073bdb0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0073bdb0 {

extern "C" undefined4 DAT_00a3d2a4;

undefined4  FUN_0073bdb0(void)
{
    if ((DAT_00a3d2a4 != 2) && (DAT_00a3d2a4 != 1)) {
        return 0;
    }
    return 1;
}

}  // namespace seed_0073bdb0
