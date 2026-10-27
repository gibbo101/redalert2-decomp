// 0x00479ca0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void FUN_00479ca0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00479ca0 {

extern "C" char DAT_00a40958;

void __stdcall FUN_00479ca0(int param_1)
{
    if (DAT_00a40958 != '\0') {
        *(int *)(param_1 + 0x194) = *(int *)(param_1 + 0x194) + -1;
    }
    return;
}

}  // namespace seed_00479ca0
