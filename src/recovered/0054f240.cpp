// 0x0054f240: function not yet identified
//
// Body: 16 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: uint __fastcall FUN_0054f240(uint *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0054f240 {

uint __fastcall FUN_0054f240(uint *param_1)
{
    return *param_1 >> 0xc & 0xf | *param_1 & 0xf;
}

}  // namespace seed_0054f240
