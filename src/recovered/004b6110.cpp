// 0x004b6110: function not yet identified
//
// Body: 96 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined1 * __thiscall FUN_004b6110(undefined1 *param_1,int param_2,undefined4 param_3,undefined4 param_4, undefined4 *param_5)
// Callees with accepted source:
//   FUN_004068f0 -> src/recovered/004068f0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004b6110 {

extern void  FUN_004068f0(int);
extern "C" undefined4 DAT_00a40d2c;
extern "C" char s_Adding_event_ANIMATION_007d68a4[];

struct Owner_004b6110 { undefined1 * FUN_004b6110(int param_2, undefined4 param_3, undefined4 param_4, undefined4 *param_5); };

undefined1 * Owner_004b6110::FUN_004b6110(int param_2, undefined4 param_3, undefined4 param_4, undefined4 *param_5)
{
    undefined1 * param_1 = (undefined1 *)this;
    FUN_004068f0((int)(s_Adding_event_ANIMATION_007d68a4));
    if (param_2 >= 0) {
        param_1[2] = (char)param_2;
        *param_1 = 0x14;
        *(undefined4 *)(param_1 + 7) = param_3;
        *(undefined4 *)(param_1 + 0xb) = param_4;
        *(undefined4 *)(param_1 + 0xf) = *param_5;
        *(undefined4 *)(param_1 + 0x13) = param_5[1];
        *(undefined4 *)(param_1 + 3) = DAT_00a40d2c;
        return param_1;
    }
    param_1[2] = 0xff;
    *param_1 = 0;
    *(undefined4 *)(param_1 + 3) = DAT_00a40d2c;
    return param_1;
}

}  // namespace seed_004b6110
