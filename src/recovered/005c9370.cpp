// 0x005c9370: function not yet identified
//
// Body: 37 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_005c9370(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c9370 {

extern "C" undefined4 DAT_00a72d34;
extern "C" undefined4 DAT_00a72d38;
extern "C" undefined4 DAT_00a72d3c;

undefined4 __fastcall FUN_005c9370(int param_1)
{
    if ((param_1 != 0) &&
          (((param_1 == DAT_00a72d34 || (param_1 == DAT_00a72d38)) || (param_1 == DAT_00a72d3c)))) {
        return 1;
    }
    return 0;
}

}  // namespace seed_005c9370
