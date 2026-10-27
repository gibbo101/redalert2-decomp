// 0x0069ae40: function not yet identified
//
// Body: 10 bytes (frozen inventory bound).
// Referenced from 7 sites (unconditional call).
// Ghidra prototype: float10 __thiscall FUN_0069ae40(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0069ae40 {

struct Owner_0069ae40 { float10 FUN_0069ae40(int param_2); };

float10 Owner_0069ae40::FUN_0069ae40(int param_2)
{
    int param_1 = (int)this;
    return (float10)*(float *)(param_1 + param_2 * 4);
}

}  // namespace seed_0069ae40
