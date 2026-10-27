// 0x0049c490: function not yet identified
//
// Owner: DisplayClass, virtual slot 45 (vtable +0xb4) (from RTTI/vtables).
// Body: 97 bytes (frozen inventory bound).
// Referenced from 8 sites (data, unconditional call).
// Ghidra prototype: void __thiscall FUN_0049c490(int param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0049c490 {

struct Owner_0049c490 { void FUN_0049c490(undefined4 *param_2); };

void Owner_0049c490::FUN_0049c490(undefined4 *param_2)
{
    int param_1 = (int)this;
    if ((((*(char *)(param_1 + 0x11ac) == '\0') && (*(char *)(param_1 + 0x11ae) == '\0')) &&
            (*(char *)(param_1 + 0x11ad) == '\0')) &&
          ((*(int *)(param_1 + 0x11b4) == -1 && (*(int *)(param_1 + 0x11a4) == 0)))) {
        *(undefined1 *)(param_1 + 0x11cc) = 1;
        *(undefined4 *)(param_1 + 0x11d0) = *param_2;
        *(undefined4 *)(param_1 + 0x11d4) = param_2[1];
        *(undefined4 *)(param_1 + 0x11d8) = *param_2;
        *(undefined4 *)(param_1 + 0x11dc) = param_2[1];
    }
    return;
}

}  // namespace seed_0049c490
