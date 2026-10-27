// 0x00430ba0: function not yet identified
//
// Body: 11 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __fastcall FUN_00430ba0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00430ba0 {

int __fastcall FUN_00430ba0(int param_1)
{
    return *(int *)(*(int *)(param_1 + 4) + 0xc) * *(int *)(param_1 + 0x24);
}

}  // namespace seed_00430ba0
