// 0x0044fa90: function not yet identified
//
// Body: 51 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_0044fa90(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0044fa90 {

void __fastcall FUN_0044fa90(int param_1)
{
    if (*(char *)(*(int *)(param_1 + 0x418) + 0x1361) != '\0') {
        *(undefined1 *)(param_1 + 0x5bb) = 1;
        if (*(char *)(param_1 + 0x5bc) == *(char *)(*(int *)(param_1 + 0x418) + 0x138b)) {
            *(undefined1 *)(param_1 + 0x5bc) = 0;
        }
        *(undefined1 *)(param_1 + 0x75) = 1;
    }
    return;
}

}  // namespace seed_0044fa90
