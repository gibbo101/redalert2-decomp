// 0x0056dba0: function not yet identified
//
// Body: 31 bytes (frozen inventory bound).
// Referenced from 14 sites (unconditional call).
// Ghidra prototype: int __fastcall FUN_0056dba0(short *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0056dba0 {

extern "C" undefined4 DAT_0084e804;
extern "C" undefined4 DAT_00a70a24;

int __fastcall FUN_0056dba0(short *param_1)
{
    return (param_1[1] * DAT_0084e804 + (int)*param_1) * 0x50 + DAT_00a70a24;
}

}  // namespace seed_0056dba0
