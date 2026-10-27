// 0x004ff170: function not yet identified
//
// Body: 46 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __thiscall FUN_004ff170(char *param_1,char *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004ff170 {

struct Owner_004ff170 { undefined4 FUN_004ff170(char *param_2); };

undefined4 Owner_004ff170::FUN_004ff170(char *param_2)
{
    char * param_1 = (char *)this;
    if (((*param_1 == *param_2) && (param_1[1] == param_2[1])) && (param_1[2] == param_2[2])) {
        return 1;
    }
    return 0;
}

}  // namespace seed_004ff170
