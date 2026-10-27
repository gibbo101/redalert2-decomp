// 0x0051d8f0: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0051d8f0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0051d8f0 {

extern undefined4  FUN_00623600(void);
extern "C" undefined4 DAT_00a3d298;

void __stdcall FUN_0051d8f0(int unused_0)
{
    if (DAT_00a3d298 == 4) {
        FUN_00623600();
    }
    return;
}

}  // namespace seed_0051d8f0
