// 0x00405140: function not yet identified
//
// Body: 16 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_00405140(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00405140 {

extern "C" undefined4 DAT_00830fb8;

undefined4 __fastcall FUN_00405140(int param_1)
{
    if (DAT_00830fb8 == 0) {
        return 0;
    }
    return *(undefined4 *)(param_1 + 0x14);
}

}  // namespace seed_00405140
