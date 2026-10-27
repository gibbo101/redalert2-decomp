// 0x006593a0: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_006593a0(int param_1,char *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006593a0 {

extern "C" undefined4 __cdecl _strncpy(...);  // @ref __strncpy=007823d0

struct Owner_006593a0 { void FUN_006593a0(char *param_2); };

void Owner_006593a0::FUN_006593a0(char *param_2)
{
    int param_1 = (int)this;
    *(undefined1 *)(param_1 + 0x293) = 0;
    _strncpy((char *)(param_1 + 400),param_2,0x103);
    return;
}

}  // namespace seed_006593a0
