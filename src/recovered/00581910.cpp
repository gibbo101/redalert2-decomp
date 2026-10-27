// 0x00581910: function not yet identified
//
// Body: 38 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 FUN_00581910(short *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00581910 {

extern "C" undefined4 DAT_0084e804;
extern "C" undefined4 DAT_00a70a24;

undefined4 __stdcall FUN_00581910(short *param_1)
{
    return *(undefined4 *)((param_1[1] * DAT_0084e804 + (int)*param_1) * 0x50 + 0x3c + DAT_00a70a24);
}

}  // namespace seed_00581910
