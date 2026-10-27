// 0x00633140: function not yet identified
//
// Body: 90 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_00633140(int param_1,undefined4 param_2)
// Callees with accepted source:
//   FUN_004068f0 -> src/recovered/004068f0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00633140 {

extern void  FUN_004068f0(int, int);
struct Callee_00632f30 { void FUN_00632f30(char param_2, char param_3); };
struct Callee_00633000 { void FUN_00633000(int param_2, undefined4 param_3); };
extern "C" undefined4 DAT_007ee350;
extern "C" void* PTR_FUN_007ee34c;
extern "C" char s_Radar__TacticalMap_availability_i_007ee324[];

struct Owner_00633140 { void FUN_00633140(undefined4 param_2); };

void Owner_00633140::FUN_00633140(undefined4 param_2)
{
    int param_1 = (int)this;
    undefined **ppuVar1;
    char cVar2;

    cVar2 = (char)param_2;
    if (*(char *)(param_1 + 0x14d4) != cVar2) {
        *(char *)(param_1 + 0x14d4) = cVar2;
        ppuVar1 = (undefined **)&DAT_007ee350;
        if (cVar2 == '\0') {
            ppuVar1 = (undefined **)(&PTR_FUN_007ee34c);
        }
        FUN_004068f0((int)(s_Radar__TacticalMap_availability_i_007ee324), (int)(ppuVar1));
        if (*(int *)(param_1 + 0x14ac) == 1) {
            ((Callee_00632f30*)(param_1))->FUN_00632f30((char)(param_2), (char)(1));
            return;
        }
        ((Callee_00633000*)(param_1))->FUN_00633000((int)(1), (undefined4)(1));
    }
    return;
}

}  // namespace seed_00633140
