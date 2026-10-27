// 0x006593e0: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_006593e0(int param_1,char *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006593e0 {

extern "C" undefined4 __cdecl _strncpy(...);  // @ref __strncpy=007823d0

struct Owner_006593e0 { void FUN_006593e0(char *param_2); };

void Owner_006593e0::FUN_006593e0(char *param_2)
{
    int param_1 = (int)this;
    *(undefined1 *)(param_1 + 0x2d3) = 0;
    _strncpy((char *)(param_1 + 0x294),param_2,0x3f);
    return;
}

}  // namespace seed_006593e0
