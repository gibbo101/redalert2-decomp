// 0x0072a840: function not yet identified
//
// Body: 46 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __thiscall FUN_0072a840(int *param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0072a840 {

struct Owner_0072a840 { undefined4 FUN_0072a840(int *param_2); };

undefined4 Owner_0072a840::FUN_0072a840(int *param_2)
{
    int * param_1 = (int *)this;
    if (((*param_1 == *param_2) && (param_1[1] == param_2[1])) && (param_1[2] == param_2[2])) {
        return 1;
    }
    return 0;
}

}  // namespace seed_0072a840
