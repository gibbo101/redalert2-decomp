// 0x00406fc0: function not yet identified
//
// Body: 18 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool __fastcall FUN_00406fc0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00406fc0 {

int __fastcall FUN_00406fc0(int param_1)
{
    return *(int *)(param_1 + 4) != *(int *)(param_1 + 8);
}

}  // namespace seed_00406fc0
