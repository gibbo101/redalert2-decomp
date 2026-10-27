// 0x0078bafa: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 4 sites (data, unconditional call).
// Ghidra prototype: void FUN_0078bafa(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078bafa {

extern undefined4  FUN_0078b712(undefined4 param_1);
extern "C" undefined4 DAT_00b2b9b0;

void  FUN_0078bafa(void)
{
    if (DAT_00b2b9b0 == 0) {
        FUN_0078b712((undefined4)(0xfffffffd));
        DAT_00b2b9b0 = 1;
    }
    return;
}

}  // namespace seed_0078bafa
