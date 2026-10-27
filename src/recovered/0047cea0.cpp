// 0x0047cea0: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_0047cea0(int param_1,double param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0047cea0 {

struct Owner_0047cea0 { void FUN_0047cea0(double param_2); };

void Owner_0047cea0::FUN_0047cea0(double param_2)
{
    int param_1 = (int)this;
    *(double *)(param_1 + 0xf0) = param_2 + *(double *)(param_1 + 0xf0);
    return;
}

}  // namespace seed_0047cea0
