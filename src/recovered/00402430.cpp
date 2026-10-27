// 0x00402430: function not yet identified
//
// Body: 10 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: uint __fastcall FUN_00402430(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00402430 {

uint __fastcall FUN_00402430(int param_1)
{
    return *(uint *)(param_1 + 0xa4) & 8;
}

}  // namespace seed_00402430
