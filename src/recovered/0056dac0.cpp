// 0x0056dac0: function not yet identified
//
// Body: 42 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool __fastcall FUN_0056dac0(short *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0056dac0 {

extern "C" undefined4 DAT_0084e804;
extern "C" undefined4 DAT_00a70a24;

bool __fastcall FUN_0056dac0(short *param_1)
{
    return *(char *)((param_1[1] * DAT_0084e804 + (int)*param_1) * 0x50 + 0x45 + DAT_00a70a24) == '\0'
    ;
}

}  // namespace seed_0056dac0
