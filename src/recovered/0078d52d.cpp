// 0x0078d52d: function not yet identified
//
// Body: 90 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_0078d52d(int param_1,uint param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078d52d {

undefined4  FUN_0078d52d(int param_1, uint param_2)
{
    undefined4 uStack_8;

    if (param_2 == 0x7ff00000) {
        if (param_1 == 0) {
            return 1;
        }
    }
    else if ((param_2 == 0xfff00000) && (param_1 == 0)) {
        return 2;
    }
    if (((*(ushort*)((char*)&param_2 + 2)) & 0x7ff8) == 0x7ff8) {
        uStack_8 = (undefined4)(3);
    }
    else {
        if ((((*(ushort*)((char*)&param_2 + 2)) & 0x7ff8) != 0x7ff0) || (((param_2 & 0x7ffff) == 0 && (param_1 == 0)))) {
            return 0;
        }
        uStack_8 = (undefined4)(4);
    }
    return uStack_8;
}

}  // namespace seed_0078d52d
