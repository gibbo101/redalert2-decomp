// 0x0078d841: function not yet identified
//
// Body: 23 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_0078d841(undefined4 param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078d841 {

extern undefined4  FUN_0078d858(LPCSTR param_1, uint param_2, uint param_3, uint param_4);

void  FUN_0078d841(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    FUN_0078d858((LPCSTR)(param_1), (uint)(param_2), (uint)(0x40), (uint)(param_3));
    return;
}

}  // namespace seed_0078d841
