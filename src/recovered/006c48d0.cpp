// 0x006c48d0: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int FUN_006c48d0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006c48d0 {

extern "C" undefined4 DAT_00839848;

int __stdcall FUN_006c48d0(int param_1)
{
    return (*(int *)(param_1 + 8) / *(int *)(DAT_00839848 + 0x1324)) * 10;
}

}  // namespace seed_006c48d0
