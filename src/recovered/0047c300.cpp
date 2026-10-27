// 0x0047c300: function not yet identified
//
// Body: 20 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: bool __thiscall FUN_0047c300(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0047c300 {

struct Owner_0047c300 { bool FUN_0047c300(int param_2); };

bool Owner_0047c300::FUN_0047c300(int param_2)
{
    int param_1 = (int)this;
    return 0 < *(short *)(param_1 + 0xac + param_2 * 2);
}

}  // namespace seed_0047c300
