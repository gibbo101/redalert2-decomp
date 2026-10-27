// 0x004788d0: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: uint __fastcall FUN_004788d0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004788d0 {

uint __fastcall FUN_004788d0(int param_1)
{
    return *(uint *)(param_1 + 0x140) >> 8 & 1;
}

}  // namespace seed_004788d0
