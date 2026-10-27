// 0x00791b15: function not yet identified
//
// Body: 66 bytes (frozen inventory bound).
// Referenced from 7 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_00791b15(uint param_1)
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

namespace seed_00791b15 {

extern undefined4  FUN_0078991e(void);
extern undefined4  FUN_00789927(void);
extern "C" undefined4 DAT_00b2b880;
extern "C" undefined4 DAT_00b2b980;

undefined4  FUN_00791b15(uint param_1)
{
    undefined4 *puVar1;

    if ((param_1 < DAT_00b2b980) &&
          ((*(byte *)((&DAT_00b2b880)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
        return *(undefined4 *)((&DAT_00b2b880)[(int)param_1 >> 5] + (param_1 & 0x1f) * 0x24);
    }
    puVar1 = (undefined4 *)FUN_0078991e();
    *puVar1 = 9;
    puVar1 = (undefined4 *)FUN_00789927();
    *puVar1 = 0;
    return 0xffffffff;
}

}  // namespace seed_00791b15
