// 0x005a08f0: function not yet identified
//
// Body: 36 bytes (frozen inventory bound).
// Referenced from 2 sites (data).
// Ghidra prototype: void __fastcall FUN_005a08f0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005a08f0 {

struct Callee_005b4da0 { undefined4 FUN_005b4da0(int, int, int, int, int, int, int); };
extern "C" undefined4 DAT_00a3dc70;

void __fastcall FUN_005a08f0(int param_1)
{
    if (param_1 != 0) {
        ((Callee_005b4da0*)(&DAT_00a3dc70))->FUN_005b4da0((int)(0), (int)(0), (int)(*(undefined4 *)(param_1 + 0x14)), (int)(0), (int)(0x4046), (int)(*(undefined4 *)(param_1 + 4)), (int)(0));
    }
    return;
}

}  // namespace seed_005a08f0
