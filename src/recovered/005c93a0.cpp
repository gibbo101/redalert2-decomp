// 0x005c93a0: function not yet identified
//
// Body: 45 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_005c93a0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c93a0 {

extern "C" undefined4 DAT_00a72d2c;
extern "C" undefined4 DAT_00a72d30;
extern "C" undefined4 DAT_00a72d40;
extern "C" undefined4 DAT_00a72d44;

undefined4 __fastcall FUN_005c93a0(int param_1)
{
    if ((((param_1 != 0) && (param_1 != DAT_00a72d2c)) && (param_1 != DAT_00a72d30)) &&
          ((param_1 != DAT_00a72d44 && (param_1 != DAT_00a72d40)))) {
        return 1;
    }
    return 0;
}

}  // namespace seed_005c93a0
