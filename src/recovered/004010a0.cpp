// 0x004010a0: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 7 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_004010a0(byte *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004010a0 {

undefined4 __fastcall FUN_004010a0(byte *param_1)
{
    if ((((*param_1 & 2) == 0) && ((param_1[0x28] & 2) == 0)) && ((param_1[0x50] & 2) == 0)) {
        return 0;
    }
    return 1;
}

}  // namespace seed_004010a0
