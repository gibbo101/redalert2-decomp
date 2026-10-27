// 0x00401620: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_00401620(int *param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00401620 {

undefined4 __fastcall FUN_00401620(int *param_1, int param_2)
{
    if ((param_2 >= 0) && (param_2 < param_1[1])) {
        return *(undefined4 *)(*param_1 + 0x14 + param_2 * 0x24);
    }
    return 0;
}

}  // namespace seed_00401620
