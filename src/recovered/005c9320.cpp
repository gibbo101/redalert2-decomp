// 0x005c9320: function not yet identified
//
// Body: 69 bytes (frozen inventory bound).
// Referenced from 7 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_005c9320(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c9320 {

extern "C" undefined4 DAT_00a72d2c;
extern "C" undefined4 DAT_00a72d30;
extern "C" undefined4 DAT_00a72d34;
extern "C" undefined4 DAT_00a72d38;
extern "C" undefined4 DAT_00a72d3c;
extern "C" undefined4 DAT_00a72d40;
extern "C" undefined4 DAT_00a72d44;

undefined4 __fastcall FUN_005c9320(int param_1)
{
    if (((((param_1 != 0) && (param_1 != DAT_00a72d2c)) && (param_1 != DAT_00a72d30)) &&
            ((param_1 != DAT_00a72d40 && (param_1 != DAT_00a72d44)))) &&
          ((param_1 != DAT_00a72d34 && ((param_1 != DAT_00a72d38 && (param_1 != DAT_00a72d3c)))))) {
        return 1;
    }
    return 0;
}

}  // namespace seed_005c9320
