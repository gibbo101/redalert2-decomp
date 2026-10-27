// 0x0042ddb0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_0042ddb0(int param_1,byte param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042ddb0 {

struct Owner_0042ddb0 { void FUN_0042ddb0(byte param_2); };

void Owner_0042ddb0::FUN_0042ddb0(byte param_2)
{
    int param_1 = (int)this;
    *(byte *)(param_1 + 0xc) = (param_2 & 1) << 1 | *(byte *)(param_1 + 0xc) & 0xfd;
    return;
}

}  // namespace seed_0042ddb0
