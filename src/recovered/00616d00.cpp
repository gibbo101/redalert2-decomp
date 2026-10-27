// 0x00616d00: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00616d00(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00616d00 {

extern "C" undefined4 DAT_00a76684;

void __fastcall FUN_00616d00(int param_1)
{
    if ((param_1 >= 0) && (param_1 < 8)) {
        (&DAT_00a76684)[param_1] = (&DAT_00a76684)[param_1] + 1;
    }
    return;
}

}  // namespace seed_00616d00
