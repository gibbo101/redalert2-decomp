// 0x00401600: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: char * __fastcall FUN_00401600(int *param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00401600 {

extern "C" char s_Invalid_007cc958[];

char * __fastcall FUN_00401600(int *param_1, int param_2)
{
    if ((param_2 >= 0) && (param_2 < param_1[1])) {
        return (char *)(*param_1 + param_2 * 0x24);
    }
    return s_Invalid_007cc958;
}

}  // namespace seed_00401600
