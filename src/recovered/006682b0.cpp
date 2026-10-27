// 0x006682b0: function not yet identified
//
// Body: 14 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_006682b0(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006682b0 {

extern void  FUN_007825e8(LPVOID param_1);

void __fastcall FUN_006682b0(int *param_1)
{
    if (*param_1 != 0) {
        FUN_007825e8((LPVOID)(*param_1));
    }
    return;
}

}  // namespace seed_006682b0
