// 0x0042bee0: function not yet identified
//
// Body: 47 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __thiscall FUN_0042bee0(int *param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042bee0 {

struct Owner_0042bee0 { undefined4 FUN_0042bee0(int *param_2); };

undefined4 Owner_0042bee0::FUN_0042bee0(int *param_2)
{
    int * param_1 = (int *)this;
    if (((*param_1 == *param_2) && ((short)param_1[1] == (short)param_2[1])) &&
          (*(short *)((int)param_1 + 6) == *(short *)((int)param_2 + 6))) {
        return 1;
    }
    return 0;
}

}  // namespace seed_0042bee0
