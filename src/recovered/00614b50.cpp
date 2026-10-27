// 0x00614b50: function not yet identified
//
// Body: 20 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: undefined1 __fastcall FUN_00614b50(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00614b50 {

extern "C" char DAT_00a767a4;

undefined1 __fastcall FUN_00614b50(int param_1)
{
    if ((DAT_00a767a4 != '\0') && (param_1 == 4)) {
        return 0;
    }
    return 1;
}

}  // namespace seed_00614b50
