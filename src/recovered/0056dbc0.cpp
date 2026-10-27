// 0x0056dbc0: function not yet identified
//
// Body: 15 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: int __fastcall FUN_0056dbc0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0056dbc0 {

extern "C" undefined4 DAT_00a70a24;

int __fastcall FUN_0056dbc0(int param_1)
{
    return param_1 * 0x50 + DAT_00a70a24;
}

}  // namespace seed_0056dbc0
