// 0x004f5b30: function not yet identified
//
// Body: 10 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: float10 __fastcall FUN_004f5b30(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004f5b30 {

float10 __fastcall FUN_004f5b30(int param_1)
{
    return (float10)*(float *)(*(int *)(param_1 + 0x34) + 0x148);
}

}  // namespace seed_004f5b30
