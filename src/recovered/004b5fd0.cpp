// 0x004b5fd0: function not yet identified
//
// Body: 87 bytes (frozen inventory bound).
// Referenced from 9 sites (unconditional call).
// Ghidra prototype: byte * __thiscall FUN_004b5fd0(byte *param_1,int param_2,byte param_3)
// Callees with accepted source:
//   FUN_004068f0 -> src/recovered/004068f0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004b5fd0 {

extern void  FUN_004068f0(int, int);
extern "C" undefined4 DAT_00a40d2c;
extern "C" void* PTR_s_EMPTY_007d65cc;
extern "C" char s_Adding_event__s_007d6890[];

struct Owner_004b5fd0 { byte * FUN_004b5fd0(int param_2, byte param_3); };

byte * Owner_004b5fd0::FUN_004b5fd0(int param_2, byte param_3)
{
    byte * param_1 = (byte *)this;
    FUN_004068f0((int)(s_Adding_event__s_007d6890), (int)((&PTR_s_EMPTY_007d65cc)[param_3]));
    if (param_2 >= 0) {
        param_1[2] = (byte)param_2;
        *param_1 = param_3;
        *(undefined4 *)(param_1 + 3) = DAT_00a40d2c;
        return param_1;
    }
    param_1[2] = 0xff;
    *param_1 = 0;
    *(undefined4 *)(param_1 + 3) = DAT_00a40d2c;
    return param_1;
}

}  // namespace seed_004b5fd0
