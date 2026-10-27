// 0x0078ad04: function not yet identified
//
// Body: 93 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_0078ad04(uint param_1)
// Callees with accepted source:
//   FUN_0078991e -> src/recovered/0078991e.cpp
//   FUN_00789927 -> src/recovered/00789927.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078ad04 {

extern undefined4  FUN_0078991e(void);
extern undefined4  FUN_00789927(void);
extern undefined4  FUN_0078ad61(uint param_1);
extern void  FUN_00791bfe(uint param_1);
extern void  FUN_00791c5d(uint param_1);
extern "C" undefined4 DAT_00b2b880;
extern "C" undefined4 DAT_00b2b980;

undefined4  FUN_0078ad04(uint param_1)
{
    undefined4 uVar1;
    undefined4 *puVar2;

    if ((param_1 < DAT_00b2b980) &&
          ((*(byte *)((&DAT_00b2b880)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
        FUN_00791bfe((uint)(param_1));
        uVar1 = (undefined4)(FUN_0078ad61((uint)(param_1)));
        FUN_00791c5d((uint)(param_1));
        return uVar1;
    }
    puVar2 = (undefined4 *)FUN_0078991e();
    *puVar2 = 9;
    puVar2 = (undefined4 *)FUN_00789927();
    *puVar2 = 0;
    return 0xffffffff;
}

}  // namespace seed_0078ad04
