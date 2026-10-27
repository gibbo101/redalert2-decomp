// 0x006f64b0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_006f64b0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006f64b0 {

struct Callee_0049cac0 { void FUN_0049cac0(int param_2); };
extern "C" undefined4 DAT_008324e0;
extern "C" undefined4 DAT_00a3d548;

void  FUN_006f64b0(void)
{
    if (DAT_00a3d548 == 0) {
        ((Callee_0049cac0*)(&DAT_008324e0))->FUN_0049cac0((int)(0xffffffff));
    }
    return;
}

}  // namespace seed_006f64b0
