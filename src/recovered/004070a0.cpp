// 0x004070a0: function not yet identified
//
// Body: 43 bytes (frozen inventory bound).
// Referenced from 26 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_004070a0(uint *param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004070a0 {

extern undefined8  FUN_004092d0(void);

void __fastcall FUN_004070a0(uint *param_1, int param_2)
{
    undefined8 uVar1;

    *param_1 = *param_1 & 0xfffffffe;
    if (param_1[2] == param_1[1]) {
        uVar1 = (undefined8)(FUN_004092d0());
        *(undefined8 *)(param_1 + 6) = uVar1;
    }
    param_1[2] = param_2 << 0x10;
    return;
}

}  // namespace seed_004070a0
